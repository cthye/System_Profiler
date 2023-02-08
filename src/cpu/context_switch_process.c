#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../utils/calculation.h"
// #include "../utils/constant.h"

const int SIZE_OF_STAT = 100; // #inner loop
const int BOUND_OF_LOOP = 100; // #outer loop


int main(int argc, char *argv[]) {
    printf("start measuring...\n");

    //* run in single core
    // cpu_set_t set;
    // CPU_ZERO(&set);
    // CPU_SET(0, &set);

    //*=========================== 
    //* create pipes
    //*===========================
    int parent_pipe[2], child_pipe[2];
    if(pipe(parent_pipe) < 0) {
        printf("failed to create pipe...\n");
        return 0;
    }
    if(pipe(child_pipe) < 0) {
        printf("failed to create pipe...\n");
        return 0;
    }

    //*=========================== 
    //* allocate memory 
    //*===========================
    uint64_t **pipe_times; // store #BOUND_OF_LOOP * SIZE_OF_STAT "time"
    pipe_times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!pipe_times) {
        printf("failed to allocate memory to times...\n");
        return 0;
    }

    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        pipe_times[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!pipe_times[i]) {
            printf("failed to allocate memory to times[%d]...\n", i);
            for(int k = 0; k < i; k++) free(pipe_times[k]);
            return 0;
        }
    }

    uint64_t** times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!times) {
        printf("failed to allocate memory to times...\n");
        return 0;
    }

    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        times[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!times[i]) {
            printf("failed to allocate memory to times[%d]...\n", i);
            for(int k = 0; k < i; k++) free(times[k]);
            return 0;
        }
    }

    unsigned cycles_high, cycles_low;
    unsigned cycles_high1, cycles_low1;
    uint64_t start, end;

    //*================================
    //* measure pure pipe r/w overhead
    //*================================
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        for(int j = 0; j < SIZE_OF_STAT; j++) {
            __asm__ __volatile__ ("CPUID\n\t"
                                    "RDTSC\n\t"
                                    "mov %%edx, %0\n\t"
                                    "mov %%eax, %1\n\t"
                                    : "=r" (cycles_high), "=r" (cycles_low)
                                    :: "%rax", "%rbx", "%rcx", "%rdx");
            write(child_pipe[1], NULL, 0);
            read(child_pipe[0], NULL, 0);
            __asm__ __volatile__ ("RDTSC\n\t"
                                    "mov %%edx, %0\n\t"
                                    "mov %%eax, %1\n\t"
                                    "CPUID\n\t"
                                    : "=r" (cycles_high1), "=r" (cycles_low1)
                                    :: "%rax", "%rbx", "%rcx", "%rdx");
            start = ((uint64_t) cycles_high << 32) | cycles_low;
            end = ((uint64_t) cycles_high1 << 32) | cycles_low1;
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
            } else {
                pipe_times[i][j]= (end - start);
            }
        }
    }

    //*================================
    //* measure context-switch overhead
    //*================================
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        for(int j = 0; j < SIZE_OF_STAT; j++) {

            pid_t pid = fork();
            if(pid == -1) {
                printf("failed to create child...\n");
                return 0;
            }

            //* ping-pong
            if(pid == 0) {
                //* in child
                // sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);
                read(child_pipe[0], NULL, 0);
                write(parent_pipe[1], NULL, 0);
                return 0;
            } else {
                //* in parent
                // sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);
                __asm__ __volatile__ ("CPUID\n\t"
                                        "RDTSC\n\t"
                                        "mov %%edx, %0\n\t"
                                        "mov %%eax, %1\n\t"
                                        : "=r" (cycles_high), "=r" (cycles_low)
                                        :: "%rax", "%rbx", "%rcx", "%rdx");
                write(child_pipe[1], NULL, 0);
                read(parent_pipe[0], NULL, 0);

                __asm__ __volatile__ ("RDTSC\n\t"
                                        "mov %%edx, %0\n\t"
                                        "mov %%eax, %1\n\t"
                                        "CPUID\n\t"
                                        : "=r" (cycles_high1), "=r" (cycles_low1)
                                        :: "%rax", "%rbx", "%rcx", "%rdx");

                start = ((uint64_t) cycles_high << 32) | cycles_low;
                end = ((uint64_t) cycles_high1 << 32) | cycles_low1;
                if((end - start) < 0) {
                    printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                } else {
                    times[i][j] = end - start;

                }
                wait(NULL);
            }
        }
    }

    //* =============================
    //* do calculation
    //*==============================
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char* filename = "stat/pipe_read_write_overhead.txt";
    do_calculation(pipe_times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("====================== pipe r/w ==================\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.2f\n", mean);
    printf("variance:%.2f\n", variance);
    printf("variance of mean:%.2f\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);

    filename = "stat/context_switch_process_overhead.txt";
    do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("====================== context switch ==================\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.2f\n", mean);
    printf("variance:%.2f\n", variance);
    printf("variance of mean:%.2f\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);
    for(int i = 0; i < BOUND_OF_LOOP; i++) {
        free(pipe_times[i]);
    }

    free(pipe_times);

    for(int i = 0; i < BOUND_OF_LOOP; i++) {
        free(times[i]);
    }

    free(times);

    return 0;
}
