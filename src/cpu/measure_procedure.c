#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include "../utils/calculation.h"
#include "../utils/constant.h"

void procedure_0() {

}

void procedure_1(uint64_t arg1) {

}

void procedure_2(uint64_t arg1, uint64_t arg2) {

}

void procedure_3(uint64_t arg1, uint64_t arg2, uint64_t arg3) {

}

void procedure_4(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4) {

}

void procedure_5(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5) {

}

void procedure_6(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6) {
    
}

void procedure_7(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6, uint64_t arg7) {
    
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage:%s -[0-7]\n", argv[0]);
        return 1;
    }
    int argn = atoi(argv[1]+1);
    printf("Measuring procedure with %d arguments\n", argn);
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
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
    for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
        //printf("Iter[%d]\n", i);
        // unrolling required
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            switch (argn)
            {
            case 0:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_0();
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
            case 1:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_1(0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
            case 2:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_2(0, 0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
                case 3:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_3(0, 0, 0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
                case 4:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_4(0, 0, 0, 0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
                case 5:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_5(0, 0, 0, 0, 0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
                case 6:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_6(0, 0, 0, 0, 0, 0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
                case 7:
                __asm__ volatile (
                "cpuid\n\t"
                "rdtsc\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r" (cycles_high0), "=r" (cycles_low0)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );
                procedure_7(0, 0, 0, 0, 0, 0, 0);
                __asm__ volatile (
                "rdtscp\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
                :: "%rax", "%rbx", "%rcx", "%rdx"
                );          
                break;
            default:
                printf("Wrong argument number\n");
                return 0;
                break;
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
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char filename[40];
    sprintf(filename, "stat/procedure%d_rst.txt", argn);
    do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("=========== Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.2f\n", mean);
    printf("variance:%.2f\n", variance);
    printf("variance of mean:%.2f\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);
}