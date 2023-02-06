#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include "../utils/constant.h"
#include "../utils/calculation.h"

void *thread(void *arg) {
    pthread_exit(NULL);
}

int main() {
    uint64_t **times;
    times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
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
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    printf("=========== Measuring Process Creation ===========\n");
    for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
        //printf("Iter[%d]\n", i);
        // unrolling required
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            pid_t pid = fork();
            __asm__ volatile(
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            if (pid == 0) {
                return 0;
            }
            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                times[i][j] = 0;
            } else {
                times[i][j] = end - start;
            }
        }
    }

    uint64_t mean = 0;
    uint64_t variance = 0;
    uint64_t variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char* filename = "../stat/task_process_rst.txt";
    do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("=========== Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%lu\n", mean);
    printf("variance:%lu\n", variance);
    printf("variance of mean:%lu\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);

    printf("=========== Measuring Thread Creation ===========\n");
    for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
        // printf("Iter[%d]\n", i);
        // unrolling required
        pthread_t tid;
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            pthread_create(&tid, NULL, thread, "child");
            __asm__ volatile(
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                times[i][j] = 0;
            } else {
                times[i][j] = end - start;
            }
        }
    }
    filename = "../stat/task_thread_rst.txt";
    do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);
    printf("=========== Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%lu\n", mean);
    printf("variance:%lu\n", variance);
    printf("variance of mean:%lu\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);
    for(int i = 0; i < BOUND_OF_LOOP; i++) {
        free(times[i]);
    }
    free(times);
}
