#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../utils/calculation.h"

#define MAX_BLOCK_READ_COUNT 1024
#define BLOCKSIZE 4096
#define BOUND_OF_LOOP 10
#define SIZE_OF_STAT 10
#define MIN_PROCESSES 2
#define MAX_PROCESSES 3
#define ULL unsigned long long
#define xMB(x) ((ULL)x * 1024 * 1024)
#define FILESIZE xMB(32)
#define NBLOCK FILESIZE / BLOCKSIZE

int main() {
    char *buffer = malloc(BLOCKSIZE * sizeof(char));
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    uint64_t **times; // store #BOUND_OF_LOOP * SIZE_OF_STAT
    times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!times) {
        printf("failed to allocate memory to times...\n");
        return -1;
    }

    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        times[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!times[i]) {
            printf("failed to allocate memory to times[%d]...\n", i);
            for(int k = 0; k < i; k++) free(times[k]);
            return -1;
        }
    }

    // output file
    char *output = "../stat/measure_contention_rst.txt";
    FILE *ofile = fopen(output, "w");
    if (!ofile) {
        printf("open file failed\n");
        return -1;
    }

    unsigned cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;

    for (int processN = MIN_PROCESSES; processN <= MAX_PROCESSES; processN += 1) {
        printf("====== Measuring with %d Processes ======\n", processN);
        for (int i = 0; i <= BOUND_OF_LOOP; i++) {
            for (int j = 0; j < SIZE_OF_STAT; j++) {
                pid_t *child_pids = malloc(sizeof(pid_t) * processN);
                uint64_t *childrenAvgReadTime = malloc(sizeof(uint64_t) * processN);

                for (int child = 0; child < processN; child += 1) {
                    pid_t child_pid = fork();
                    if (child_pid == 0) { // child
                        uint64_t sum = 0;
                        char *filename = malloc(50 * sizeof(char));
                        sprintf(filename, "./testfile_%d", child);
                        int fd = open(filename, O_RDONLY | O_DIRECT);
                        if (!fd) {
                            printf("open file %s failed\n", filename);
                            return 0;
                        }

                        for (ULL n = 0; n < NBLOCK; n += 1) {
                            __asm__ volatile(
                            "cpuid\n\t"
                            "rdtsc\n\t"
                            "mov %%edx, %0\n\t"
                            "mov %%eax, %1\n\t"
                            : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

                            read(fd, buffer, BLOCKSIZE);

                            __asm__ volatile(
                            "rdtscp\n\t"
                            "mov %%edx, %0\n\t"
                            "mov %%eax, %1\n\t"
                            "cpuid\n\t"
                            : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

                            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
                            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
                            if((end - start) < 0) {
                                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                            } else {
                                sum += (end - start);
                            }
                            posix_fadvise(fd, n * BLOCKSIZE, BLOCKSIZE, POSIX_FADV_DONTNEED);
                        }
                        childrenAvgReadTime[child] = sum / NBLOCK;
                        close(fd);
                        return 0; // end child
                    } else {
                        child_pids[child] = child_pid;
                    }
                }
                for (int n = 0; n < processN; n += 1) {
                    wait(&child_pids[n]);
                }
                uint64_t allChildrenSum = 0;
                for(int n = 0; n < processN; n += 1) {
                    allChildrenSum += childrenAvgReadTime[n];
                }
                times[i][j] = allChildrenSum / processN;
                free(child_pids);
                free(childrenAvgReadTime);
            }
        }
        char* filename = malloc(50 * sizeof(char));
        sprintf(filename, "../stat/measure_contention_%dprocesses", processN);
        do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);
        printf("====================== Statistics of Reading file with %d Processes ==================\n", processN);
        printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
        printf("mean per block:%.2f\n", mean);
        printf("variance:%.2f\n", variance);
        printf("variance of mean:%.2f\n", variance_of_mean);
        printf("maximum deviation:%lu\n", max_deviation);
        fprintf(ofile, "%d %.2f\n", processN, mean);
    }
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        free(times[i]);
    }
    free(times);
    return 0;

    // for (int i = 0; i <= BOUND_OF_LOOP; i++)
    // {
    //     for (int child = 1; child <= num_of_child_process; child++)
    //     {
    //         printf("child:%d accessing file", child);
    //         char child_file_name[sizeof(filename) + 100];
    //         sprintf(child_file_name, "%s%d", filename, child);

    //         pid_t child_pid = fork();
    //         if (child_pid == 0)
    //         {
    //             int file_fd;
    //             int status;

    //             /* open the file for reading */
    //             FILE *fd = fopen(child_file_name, "r"); // file's name /media/stevie/SSD1/testfile1; /media/stevie/SSD1/testfile2 ...
    //             if (!fd)
    //             {
    //                 printf("open file failed\n");
    //                 return -1;
    //             }
    //             // read file
    //             warmup(fd, buffer, read_file_size);
    //             fseek(fd, 0, SEEK_SET);
    //             unsigned cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    //             uint64_t start, end;
    //             ULL blockn = read_file_size / BLOCKSIZE;
    //             unsigned t_sum = 0;
    //             for (ULL i = 0; i < blockn; i += 1)
    //             {
    //                 __asm__ volatile(
    //                 "cpuid\n\t"
    //                 "rdtsc\n\t"
    //                 "mov %%edx, %0\n\t"
    //                 "mov %%eax, %1\n\t"
    //                 : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");
    //                 fread(buffer, BLOCKSIZE, 1, fd);
    //                 __asm__ volatile(
    //                 "rdtscp\n\t"
    //                 "mov %%edx, %0\n\t"
    //                 "mov %%eax, %1\n\t"
    //                 "cpuid\n\t"
    //                 : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");
    //                 start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
    //                 end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
    //                 if((end - start) < 0) {
    //                     printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
    //                 } else {
    //                     t_sum += end - start;
    //                 }
    //                 posix_fadvise(fd, i * BLOCKSIZE, BLOCKSIZE, POSIX_FADV_DONTNEED);
    //             }
    //             times[i][child] = t_sum/(xMB(32)/BLOCKSIZE); //record average cycles of accessing 1 block

    //             // close the file
    //             status = close(file_fd);
    //             if (status < 0){
    //                 printf("close file failed\n");
    //                 return -1;
    //             }
    //             return 0;
    //         }
    //         else
    //         {
    //             printf("Parent - child:%d launched\n", child);
    //             child_pids[child - 1] = child_pid;
    //         }
    //     }
    //     // make parent wait for childs to finish
    //     for (int i = 0; i < num_of_child_process; i++)
    //         wait(&child_pids[i]);
    // }

    // char *filename = malloc(50 * sizeof(char));
    // sprintf(filename, "../stat/contention_%lluchildProcess", NUM_OF_CHILD);
    // do_calculation(times + 1, BOUND_OF_LOOP, NUM_OF_CHILD, &mean, &variance, &variance_of_mean, &max_deviation, filename);
    // printf("====================== Statistics of Reading %llu different %llu GB size files simultaniously ==================\n", NUM_OF_CHILD, read_file_size / xGB(1));
    // printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, NUM_OF_CHILD);
    // printf("mean per block:%.2f\n", mean);
    // printf("variance:%.2f\n", variance);
    // printf("variance of mean:%.2f\n", variance_of_mean);
    // printf("maximum deviation:%lu\n", max_deviation);
    // fprintf(ofile, "%llu %.2f\n", read_file_size / xGB(1), mean);

    // for(int i = 0; i <= BOUND_OF_LOOP; i++) {
    //     free(times[i]);
    // }
    // free(times);

    // return 0;
}