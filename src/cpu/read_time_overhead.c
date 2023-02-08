#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/calculation.h"
#include "../utils/constant.h"

int main(int argc, char *argv[]) {
    uint64_t **times; // store #BOUND_OF_LOOP * SIZE_OF_STAT "time"
    // uint64_t *min_values; // store #BOUND_OF_LOOP "min_value" 

    printf("start measuring...\n");

    //*=========================== 
    //* allocate memory 
    //*===========================
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

    //* =============================
    //* measure overhead of measuring
    //*==============================
    unsigned cycles_high, cycles_low;
    unsigned cycles_high1, cycles_low1;

    //* cache warmup
    __asm__ __volatile__ ("CPUID\n\t"
                        "RDTSC\n\t"
                        "mov %%edx, %0\n\t"
                        "mov %%eax, %1\n\t"
                        : "=r" (cycles_high), "=r" (cycles_low)
                        :: "%rax", "%rbx", "%rcx", "%rdx");
    __asm__ __volatile__ ("RDTSC\n\t"
                        "mov %%edx, %0\n\t"
                        "mov %%eax, %1\n\t"
                        "CPUID\n\t"
                        : "=r" (cycles_high1), "=r" (cycles_low1)
                        :: "%rax", "%rbx", "%rcx", "%rdx");
    __asm__ __volatile__ ("CPUID\n\t"
                        "RDTSC\n\t"
                        "mov %%edx, %0\n\t"
                        "mov %%eax, %1\n\t"
                        : "=r" (cycles_high), "=r" (cycles_low)
                        :: "%rax", "%rbx", "%rcx", "%rdx");
    __asm__ __volatile__ ("RDTSC\n\t"
                        "mov %%edx, %0\n\t"
                        "mov %%eax, %1\n\t"
                        "CPUID\n\t"
                        : "=r" (cycles_high1), "=r" (cycles_low1)
                        :: "%rax", "%rbx", "%rcx", "%rdx");

    uint64_t start, end;
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        for(int j = 0; j < SIZE_OF_STAT; j++) {
            // preempt_disable();
            // raw_local_irq_save(flags);

            __asm__ __volatile__ ("CPUID\n\t"
                                "RDTSC\n\t"
                                "mov %%edx, %0\n\t"
                                "mov %%eax, %1\n\t"
                                : "=r" (cycles_high), "=r" (cycles_low)
                                :: "%rax", "%rbx", "%rcx", "%rdx");
            
            __asm__ __volatile__ ("RDTSC\n\t"
                                "mov %%edx, %0\n\t"
                                "mov %%eax, %1\n\t"
                                "CPUID\n\t"
                                : "=r" (cycles_high1), "=r" (cycles_low1)
                                :: "%rax", "%rbx", "%rcx", "%rdx");

            // raw_local_irq_restore(flags);
            // preempt_enable();

            start = ((uint64_t) cycles_high << 32) | cycles_low;
            end = ((uint64_t) cycles_high1 << 32) | cycles_low1;
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                times[i][j] = 0;
            } else {
                times[i][j] = end - start;
            }
        }
    }

    //* =============================
    //* do calculation
    //*==============================
<<<<<<< HEAD
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
=======
    uint64_t mean = 0;
    uint64_t variance = 0;
    uint64_t variance_of_mean = 0;
>>>>>>> main
    uint64_t max_deviation = 0;
    char* filename = "stat/read_time_overhead.txt";
    do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("================================================\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
<<<<<<< HEAD
    printf("mean:%.2f\n", mean);
    printf("variance:%.2f\n", variance);
    printf("variance of mean:%.2f\n", variance_of_mean);
=======
    printf("mean:%lu\n", mean);
    printf("variance:%lu\n", variance);
    printf("variance of mean:%lu\n", variance_of_mean);
>>>>>>> main
    printf("maximum deviation:%lu\n", max_deviation);

    //*=========================== 
    //* free memory 
    //*===========================
    for(int i = 0; i < BOUND_OF_LOOP; i++) {
        free(times[i]);
    }

    free(times);

    return 0;
}
