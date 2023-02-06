#ifndef CALCULATION_H
#define CALCULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//* calculate the standard variance
//*
//* @param times: times array
//* @param mean: mean of the time array
//* @param size_of_stat: size of inner loop
//* @return: standard variance of time array
extern inline uint64_t cal_variance(uint64_t* times, uint64_t mean, uint64_t size) {
    uint64_t sum = 0;
    for(int i = 0; i < size; i++) {
        sum  += (times[i] - mean) * (times[i] - mean);
    }
    return sqrt(sum / size);
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
                            uint64_t* mean, uint64_t* variance, 
                            uint64_t* variance_of_mean, uint64_t* max_deviation, const char* filename) {
                                uint64_t min_time = INT64_MAX;
                                uint64_t max_time = 0;
                                uint64_t sum_mean = 0;
                                uint64_t sum_variance = 0;
                                *mean = 0;
                                *variance = 0;
                                *variance_of_mean = 0;
                                *max_deviation = 0;

                                uint64_t* means = malloc(bound_of_loop * sizeof(uint64_t));
                                uint64_t* variances = malloc(bound_of_loop * sizeof(uint64_t));

                                FILE *fd = fopen(filename, "w");
                                if(!fd) {
                                    printf("open file failed");
                                    return;
                                }
                                fprintf(fd, "================================ raw data ===========================\n");
                                for(int i = 0; i < bound_of_loop; i++) {
                                    uint64_t sum = 0;
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
                                    variances[i] = cal_variance(times[i], means[i], bound_of_loop);
                                    sum_variance += variances[i];
                                }
                                *mean = sum_mean / bound_of_loop;
                                *variance = sum_variance / bound_of_loop;
                                *variance_of_mean = cal_variance(means, *mean, bound_of_loop);

                                fprintf(fd, "====================================================================\n");
                                fprintf(fd, "batch size: %d, size of statistic: %d\n", bound_of_loop, size_of_stat);
                                fprintf(fd, "mean:%lu\n", *mean);
                                fprintf(fd, "variance:%lu\n", *variance);
                                fprintf(fd, "variance of mean:%lu\n", *variance_of_mean);
                                fprintf(fd, "maximum deviation:%lu\n", *max_deviation);
                                fclose(fd);
                            }

#endif