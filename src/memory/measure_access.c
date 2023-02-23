#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_OF_STAT 100 // inner loop
#define BOUND_OF_LOOP 10 // outer loop
#define MINBYTES (1 << 10)  // Working set size ranges from 1 KB
#define MAXBYTES (1 << 26)  // up to 64 MB
// #define MAXBYTES (1 << 23)  // up to 8 MB
#define MAXSTRIDE 48        // Strides range from 1 to 48
// #define MAXSTRIDE 5      
#define STRIDESTRIDE 2      // increment stride by this amount each time
#define TYPE double
#define MAXELEMS MAXBYTES / sizeof(TYPE)

TYPE data[MAXELEMS];
/**
 * @brief return the throughput when accessing the array of size *size* with stride *stride*
 * 
 * @param size how big the array is in bytes
 * @param stride the stride to access the array
 * @param Mhz the CPU frequency
 * @return the throughput
 */
double run(int size, int stride, double Mhz) {
    int elements = size / sizeof(TYPE);
    uint64_t sum = 0;
    if (elements > MAXELEMS) {
        printf("Inappropriate argumetns...\n");
        return 0;
    }
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    TYPE rst0, rst1, rst2, rst3;
    volatile TYPE sink;
    // warm up the cache
    for (int k = 0; k < elements; k += stride) {
        rst0 += data[k];
        // rst1 += data[k + stride];
        // rst2 += data[k + stride * 2];
        // rst3 += data[k + stride * 3];
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

            for (int k = 0; k < elements; k += stride) {
                rst0 += data[k];
                // rst1 += data[k + stride];
                // rst2 += data[k + stride * 2];
                // rst3 += data[k + stride * 3];
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
            if(cycle <= 0) {
                printf("invalid data when calculating memory access time, start - end:%lu\n", cycle);
            } else {
                sum += cycle;
            }
            // sink = rst0 + rst1 + rst2 + rst3;
            // sink += rst0;
            data[0] = rst0;
        }
    }
    double mean = sum / (BOUND_OF_LOOP * SIZE_OF_STAT);
    return (size / stride) / (mean / Mhz);
}

void init_data(TYPE *data, int n) {
    for (int i = 0; i < n; i += 1) {
	    data[i] = 1;
    }
}

double mhz() {
    printf("====== Measuring CPU frequency ======\n");
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
    rate = (end - start) / (1e6 * 2);
    printf("Running on a %.2f Mhz CPU\n", rate);
    return rate;
}

int main() {
    char *rstfile = "../stat/memory_access_rst.txt";
    char *datafile = "../stat/memory_access_data.txt";
    FILE *rstfd = fopen(rstfile, "w");
    FILE *datafd = fopen(datafile, "w");
    if (!rstfd) {
        printf("open file %s failed", rstfile);
        return 0;
    }
    if (!datafd) {
        printf("open file %s failed", datafile);
        return 0;
    }
    init_data(data, MAXELEMS);
    double Mhz = mhz();
    double rst;
    for (int stride = 2; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
        fprintf(rstfd, "====== with %lu bytes stride ======\n", stride * sizeof(TYPE));
        for (int arraysize = MINBYTES; arraysize <= MAXBYTES; arraysize <<= 1) {
            printf("====== Measuring %d KB with %lu bytes stride ======\n", arraysize / 1024, stride * sizeof(TYPE));
            rst = run(arraysize, stride, Mhz);
            fprintf(rstfd, "elements: %d KB, stride: %lu bytes, throughput: %.2f M/s\n", arraysize / 1024, stride * sizeof(TYPE), rst);
            fprintf(datafd, "%d %d %.2f\n", stride, arraysize, rst);
        }
    }
    fprintf(rstfd, "\n");
    fprintf(datafd, "\n");
    fclose(rstfd);
    fclose(datafd);
    return 0;
}