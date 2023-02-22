#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../utils/calculation.h"

#define SIZE_OF_STAT 100 // inner loop
#define BOUND_OF_LOOP 100 // outer loop
#define MINBYTES (1 << 10)  // Working set size ranges from 1 KB
// #define MAXBYTES (1 << 25)  // up to 32 MB
#define MAXBYTES (1 << 23)  // up to 32 MB
// #define MAXSTRIDE 32        // Strides range from 1 to 32
#define MAXSTRIDE 5        // Strides range from 1 to 32
#define STRIDESTRIDE 2      // increment stride by this amount each time
#define MAXELEMS MAXBYTES / sizeof(int) 

int data[MAXELEMS];
/**
 * @brief return the throughput when accessing the array of size *size* with stride *stride*
 * 
 * @param size how big the array is in bytes
 * @param stride the stride to access the array
 * @param Mhz the CPU frequency
 * @param min return the min 
 * @return the min throughput
 */
double run(int size, int stride, double Mhz) {
    int elements = size / sizeof(int);
    uint64_t min = INT64_MAX;
    if (elements > MAXELEMS) {
        printf("Inappropriate argumetns...\n");
        return 0;
    }
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    long rst0, rst1, rst2, rst3;
    volatile int sink;
    // warm up the cache
    for (int k = 0; k < elements; k += (4 * stride)) {
        rst0 += data[k];
        rst1 += data[k + stride];
        rst2 += data[k + stride * 2];
        rst3 += data[k + stride * 3];
    }
    for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );

            for (int k = 0; k < elements; k += (4 * stride)) {
                rst0 += data[k];
                rst1 += data[k + stride];
                rst2 += data[k + stride * 2];
                rst3 += data[k + stride * 3];
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
            uint64_t cycle = end - start;
            if(cycle < 0) {
                printf("invalid data when calculating memory access time, start - end:%lu\n", cycle);
            } else if (cycle < min) {
                min = cycle;
            }
            sink = rst0 + rst1 + rst2 + rst3;
        }
    }
    return (size / stride) / (min / Mhz);
}

void init_data(int *data, int n) {
    for (int i = 0; i < n; i += 1) {
	    data[i] = 1;
    }
}

double mhz() {
    double rate;
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
    sleep(2);
    __asm__ volatile(
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
    start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
    end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
    rate = (start - end) / (1e6 * 2);
    printf("Running on a %.2f Mhz CPU\n", rate);
    return rate;
}

int main() {
    char *datafile = "../stat/memory_access_rst.txt";
    FILE *fd = fopen(datafile, "w");
    if (!fd) {
        printf("open file %s failed", datafile);
        return 0;
    }
    init_data(data, MAXELEMS);
    double Mhz = mhz();
    double rst;
    for (int stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
        fprintf(fd, "====== with %d bytes stride ======\n", stride * 4);
        for (int arraysize = MINBYTES; arraysize <= MAXBYTES; arraysize <<= 1) {
            printf("====== Measuring %.2f KB bytes with %d bytes stride ======\n", arraysize / 1024.0, stride * 4);
            rst = run(arraysize, stride, Mhz);
            fprintf(fd, "elements: %.2f KB, stride: %d bytes, throughput: %.2f M/s\n", arraysize / 1024.0, stride * 4, rst);
        }
    }
    fclose(fd);
    return 0;
}