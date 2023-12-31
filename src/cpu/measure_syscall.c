#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/times.h>
#include "../utils/constant.h"
#include "../utils/calculation.h"

#define SIZE_OF_STAT 100
#define BOUND_OF_LOOP 100

int main() {
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    uint64_t **rst;
    rst = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!rst) {
        printf("failed to allocate memory to rst...\n");
        return 0;
    }
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        rst[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!rst[i]) {
            printf("failed to allocate memory to rst[%d]...\n", i);
            for(int k = 0; k < i; k++) free(rst[k]);
            return 0;
        }
    }
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
            times(NULL);
            __asm__ volatile (
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
                rst[i][j] = 0;
            } else {
                rst[i][j] = end - start;
            }
        }
    }
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char* filename = "stat/syscall_rst.txt";
    do_calculation(rst + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("=========== Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.2f\n", mean);
    printf("variance:%.2f\n", variance);
    printf("variance of mean:%.2f\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);
}