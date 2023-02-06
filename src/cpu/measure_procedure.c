#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#define SIZE_OF_STAT 1000
#define BOUND_OF_LOOP 100

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

int main() {
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    double means[BOUND_OF_LOOP];
    double mean_all = 0;
    double sd = 0;
    double sum_temp = 0;
    for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
        printf("Iter[%d]\n", i);
        uint64_t sum = 0;
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
            procedure_7(0, 0, 0, 0, 0, 0, 0);
            __asm__ volatile(
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            sum += (end - start);
            printf("%lu ", end - start);
            if (j != 0 && j % 20 == 0) {
                printf("\n");
            }
        }
        means[i] = (double)sum / SIZE_OF_STAT;
        printf("\nIter[%d] mean: %f\n", i, means[i]);
    }
    for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
        mean_all += means[i];
    }
    mean_all /= BOUND_OF_LOOP;
    for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
        sum_temp += pow((means[i] - mean_all), 2);
    }
    sd = sqrt(sum_temp / BOUND_OF_LOOP);
    printf("Overall Mean: %f\nDeviation: %f", mean_all, sd);
}