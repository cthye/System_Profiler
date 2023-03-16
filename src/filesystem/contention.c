#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>
#include "../utils/calculation.h"

#define MAX_BLOCK_READ_COUNT 1024
#define BLOCKSIZE 4096
#define BOUND_OF_LOOP 10
#define SIZE_OF_STAT 20
#define MIN_PROCESSES 6
// #define MIN_PROCESSES 12
#define MAX_PROCESSES 16
#define ULL unsigned long long
#define xMB(x) ((ULL)x * 1024 * 1024)
#define FILESIZE xMB(32)
// #define FILESIZE xMB(1)
#define NBLOCK (FILESIZE / BLOCKSIZE)

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
    double *rst = malloc((MAX_PROCESSES - MIN_PROCESSES) * sizeof(double));
    if(!rst) {
        printf("allocate rst array failed...\n");
        return 0;
    }

    unsigned cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;

    for (int processN = MIN_PROCESSES; processN <= MAX_PROCESSES; processN += 1) {
        printf("====== Measuring with %d Processes ======\n", processN);
        for (int i = 0; i <= BOUND_OF_LOOP; i++) {
            for (int j = 0; j < SIZE_OF_STAT; j++) {
                pid_t *child_pids = malloc(sizeof(pid_t) * processN);
                uint64_t *childrenAvgReadTime = malloc(sizeof(uint64_t) * processN);
                int pipes[processN][2];
                for (int p = 0; p < processN; p++) {
                    pipe(pipes[p]);
                }

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
                        close(pipes[child][0]); // no reading

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
                        // printf("child:%d, sum: %llu, sum / NBLOCK: %llu\n", child, sum, sum / NBLOCK);
                        // if (sum == 0 ) {
                            // printf(" zero !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                        // }
                        childrenAvgReadTime[child] = sum / NBLOCK;
                        assert(childrenAvgReadTime[child] > 0);
                        write(pipes[child][1], &childrenAvgReadTime[child], sizeof(uint64_t));
                        close(pipes[child][1]);
                        close(fd);
                        return 0; // end child
                    } 
                }
                for (int p = 0; p < processN; p++) {
                    pid_t pid = wait(0);
                    // printf("child %d done\n", pid);
                }
                for (int p = 0; p < processN; p++) {
                    close(pipes[p][1]);
                }
                for (int n = 0; n < processN; n += 1) {
                    read(pipes[n][0], &childrenAvgReadTime[n], sizeof(uint64_t));
                    close(pipes[n][0]);
                    // printf("childrenAvgReadTime[%d] %llu\n", n, childrenAvgReadTime[n]);
                    assert(childrenAvgReadTime[n] > 0);
                    // if (n == processN - 1) {
                        // printf("done\n");
                    // }
                }
                uint64_t allChildrenSum = 0;
                for(int n = 0; n < processN; n += 1) {
                    // printf("childrenAvgReadTime[%d] %llu\n", n, childrenAvgReadTime[n]);
                    assert(childrenAvgReadTime[n] > 0);
                    allChildrenSum += childrenAvgReadTime[n];
                }
                assert(allChildrenSum > 0);
                // printf("allchildrensum %llu\n", allChildrenSum);
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
        rst[processN - MIN_PROCESSES] = mean;
        // fprintf(ofile, "%d %.2f\n", processN, mean);
    }
    for (int i = MIN_PROCESSES; i <= MAX_PROCESSES; i += 1) {
        fprintf(ofile, "%d %.2f\n", i, rst[i - MIN_PROCESSES]);
    }
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        free(times[i]);
    }
    free(times);
    return 0;
}
