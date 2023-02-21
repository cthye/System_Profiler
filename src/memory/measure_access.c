#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/calculation.h"
#include "../utils/constant.h"

#define MAXELEMS 2100000
long data[MAXELEMS]; // all the data

long test(int elements, int stride, double *mean) {
    // allocate time matrix
    if (stride <= 0 || elements >= MAXELEMS) {
        printf("Inappropriate argumetns...\n");
        return 0;
    }
    uint64_t **times;
    uint64_t sum = 0;
    times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*));
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
    uint64_t start, end, loop_overhead;
    long begin;
    long rst0, rst1, rst2, rst3;
    long length = elements, limit = length - stride * 4;

    for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );

            for (begin = 0; begin < limit; begin += (4 * stride)) {
                rst0 += data[0];
                rst1 += data[0];
                rst2 += data[0];
                rst3 += data[0];
            }
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
                printf("wrong timing when calculating the loop overhead: start:%lu, end:%lu ...\n", start, end);
                loop_overhead = 0;
            } else {
                loop_overhead = end - start;
            }

            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );

            for (begin = 0; begin < limit; begin += (4 * stride)) {
                rst0 += data[begin];
                rst1 += data[begin + stride];
                rst2 += data[begin + stride * 2];
                rst3 += data[begin + stride * 3];
            }
            // for (; begin < length; begin += 1) {
            //     rst0 += data[begin];
            // }
            __asm__ volatile(
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            if((end - start) < loop_overhead) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                times[i][j] = 0;
            } else {
                times[i][j] = end - start - loop_overhead;
            }
        }
    }
    //char *filename = "../stat/memory_access.txt";
    for (int i = 1; i <= BOUND_OF_LOOP; i += 1) {
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            sum += times[i][j];
        }
    }
    *mean = (double)(sum) / (BOUND_OF_LOOP * SIZE_OF_STAT);
    //do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, mean, variance, variance_of_mean, max_deviation, filename);
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        free(times[i]);
    }
    free(times);
    return rst0 + rst1 + rst2 + rst3;
}

double getThroughput(int elements, int stride, double mean) {
    return (8.0 * elements / stride) * 3100 / mean; // M/s
}

int main() {
    double mean = 0;
    //double variance = 0, variance_of_mean = 0;
    //uint64_t max_deviation = 0;
    char *datafile = "../stat/memory_access_rst.txt";
    FILE *fd = fopen(datafile, "w");
    if (!fd) {
        printf("open file %s failed", datafile);
        return 0;
    }
    for (int stride = 1; stride <= 16; stride += 1) {
        for (int arraysize = 8; arraysize <= 10; arraysize += 1) {
            int elements = 2 << arraysize;
            printf("====== Measuring %d elements with %d stride ======\n", elements * 8, stride * 8);
            test(elements, stride, &mean);
            fprintf(fd, "elements: %d bytes, stride: %d bytes, throughput: %.2f M/s\n", elements * 8, stride * 8, getThroughput(elements, stride, mean));
        }
    }
    fclose(fd);
    return 0;
}