#ifndef CALCULATION_H
#define CALCULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
//* calculate the standard variance
//*
//* @param times: times array
//* @param mean: mean of the time array
//* @param size_of_stat: size of inner loop
//* @return: standard variance of time array
extern inline double cal_variance_double(double* times, double mean, uint64_t size) {
    double sum = 0;
    for(int i = 0; i < size; i++) {
        sum  += (times[i] - mean) * (times[i] - mean);
    }
    return sqrt(sum / (double)size);
}

extern inline double cal_variance_uint64(uint64_t* times, double mean, uint64_t size) {
    double sum = 0;
    for(int i = 0; i < size; i++) {
        sum  += (times[i] - mean) * (times[i] - mean);
    }
    return sqrt(sum / (double)size);
}

//* do the calculation
//*
//* @param times: times array
//* @param bound_of_loop: size of outer loop
//* @param size_of_stat: size of inner loop
//* @param mean: calculate the mean of each batch, return the average of mean
//* @param variance: calculate the variance of each batch, return the average of variance
//* @param variance_of_mean: return the variance of mean
//* @param max_deviation: return the maximum deviation
//* @param filename: statistic log filename
extern inline void do_calculation(uint64_t **times, int bound_of_loop, int size_of_stat, 
                            double* mean, double* variance, 
                            double* variance_of_mean, uint64_t* max_deviation, const char* filename) {
                                uint64_t min_time = INT64_MAX;
                                uint64_t max_time = 0;
                                double sum_mean = 0;
                                double sum_variance = 0;
                                *mean = 0;
                                *variance = 0;
                                *variance_of_mean = 0;
                                *max_deviation = 0;

                                double* means = malloc(bound_of_loop * sizeof(double));
                                double* variances = malloc(bound_of_loop * sizeof(double));

                                FILE *fd = fopen(filename, "w");
                                if(!fd) {
                                    printf("open file failed");
                                    return;
                                }
                                fprintf(fd, "================================ raw data ===========================\n");
                                for(int i = 0; i < bound_of_loop; i++) {
                                    double sum = 0;
                                    for(int j = 0; j < size_of_stat; j++) {
                                        fprintf(fd, "times %d(batch) : %d -- %lu\n", i, j, times[i][j]);
                                        min_time = min_time < times[i][j] ? min_time : times[i][j];
                                        max_time = max_time > times[i][j] ? max_time : times[i][j];
                                        sum += times[i][j];
                                    }
                                    means[i] = sum / size_of_stat;
                                    sum_mean += means[i];
                                    uint64_t curr_deviation = max_time - min_time;
                                    // if(curr_deviation > 1000) {
                                    //     printf("spurious %lu %lu %lu\n", curr_deviation, max_time, min_time);
                                    // }
                                    *max_deviation = (*max_deviation) > curr_deviation ? (*max_deviation) : curr_deviation;
                                    variances[i] = cal_variance_uint64(times[i], means[i], bound_of_loop);
                                    // printf("mean%f, variance%f\n", means[i], variances[i]);

                                    sum_variance += variances[i];
                                }
                                *mean = sum_mean / bound_of_loop;
                                *variance = sum_variance / bound_of_loop;
                                // printf("sum mean%f, sum variance%f\n", sum_mean, sum_variance);
                                *variance_of_mean = cal_variance_double(means, *mean, bound_of_loop);

                                fprintf(fd, "====================================================================\n");
                                fprintf(fd, "batch size: %d, size of statistic: %d\n", bound_of_loop, size_of_stat);
                                fprintf(fd, "mean:%f\n", *mean);
                                fprintf(fd, "variance:%f\n", *variance);
                                fprintf(fd, "variance of mean:%.2f\n", *variance_of_mean);
                                fprintf(fd, "maximum deviation:%lu\n", *max_deviation);
                                fclose(fd);
                            }


//* return the MB/s
//*
//* @param size: array size (the size of total r/w array)
//* @param stride: the stride between each r/w
//* @param cycles: clock cycles elapsed
//* @return: MB/s
extern double get_throughput(long size, int stride, double cycles) {
    double freq;
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
    freq = (end - start) / (1e6 * 2);
    // printf("Running on a %.2f Mhz CPU\n", freq);

    return (size / stride) / (cycles / freq);
}

// calculate current Mhz
double calc_mhz() {
    printf("====== Measuring CPU frequency ======\n");
    double rate;
    unsigned cycles_low0, cycles_high0, cycles_low1, cycles_high1;
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

#endif