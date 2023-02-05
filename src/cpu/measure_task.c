#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#define SIZE_OF_STAT 10
#define BOUND_OF_LOOP 10

void *thread(void *arg) {
    pthread_exit(NULL);
}

int main() {
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    double means[BOUND_OF_LOOP];
    // instruction cache warm up
    __asm__ volatile (
    "cpuid\n\t"
    "rdtsc\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    : "=r" (cycles_high0), "=r" (cycles_low0)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    __asm__ volatile(
    "rdtscp\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    __asm__ volatile (
    "cpuid\n\t"
    "rdtsc\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    : "=r" (cycles_high0), "=r" (cycles_low0)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    __asm__ volatile(
    "rdtscp\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    __asm__ volatile (
    "cpuid\n\t"
    "rdtsc\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    : "=r" (cycles_high0), "=r" (cycles_low0)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    __asm__ volatile(
    "rdtscp\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    printf("=========== Measuring Process Creation ===========\n");
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
            int pid = fork();
            __asm__ volatile(
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            if (pid == 0) {
                exit(1);
            } else {
                wait(NULL);
                start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
                end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
                sum += (end - start);
                printf("%lu ", end - start);
                if (j != 0 && j % 20 == 0) {
                    printf("\n");
                }
            }
        }
        means[i] = (double)sum / SIZE_OF_STAT;
        printf("\nIter[%d] mean: %f\n", i, means[i]);
    }
    double mean_all = 0;
    double sd = 0;
    double sum_temp = 0;
    for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
        mean_all += means[i];
    }
    mean_all /= BOUND_OF_LOOP;
    for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
        sum_temp += pow((means[i] - mean_all), 2);
    }
    sd = sqrt(sum_temp / BOUND_OF_LOOP);
    printf("Overall Mean: %f\nDeviation: %f\n", mean_all, sd);
    

   printf("=========== Measuring Thread Creation ===========\n");
   for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
       printf("Iter[%d]\n", i);
       uint64_t sum = 0;
       pthread_t tid;
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
           sum += (end - start);
           printf("%lu ", end - start);
           if (j != 0 && j % 20 == 0) {
               printf("\n");
           }
       }
       means[i] = (double)sum / SIZE_OF_STAT;
       printf("\nIter[%d] mean: %f\n", i, means[i]);
   }
   mean_all = 0;
   sd = 0;
   sum_temp = 0;
   for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
       mean_all += means[i];
   }
   mean_all /= BOUND_OF_LOOP;
   for (int i = 0; i < BOUND_OF_LOOP; i += 1) {
       sum_temp += pow((means[i] - mean_all), 2);
   }
   sd = sqrt(sum_temp / BOUND_OF_LOOP);
   printf("Overall Mean: %f\nDeviation: %f\n", mean_all, sd);
}
