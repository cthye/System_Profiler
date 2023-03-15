#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <time.h>

#include "../utils/calculation.h"
// #include "../utils/constant.h"

const char* local_dir = "files";
const char* remote_dir = "nfs";
const int BLOCK_SIZE = 4096;

char* filename = "test";
char* dat_file;
char* rst_file;
double mhz;
int start_block_num;
int end_block_num;
int step;
int SIZE_OF_STAT;
int BOUND_OF_LOOP;

void shuffle(int* arr, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main(int argc, char *argv[]) {
    mhz = calc_mhz();
    //*================================
    //* parse command & set up 
    //*================================
    const char* path;
    int isSequential;
    if(argc < 3) {
        printf("command not correct, e.g. ./read_file remote sequential or ./read_file local random\n");
        return -1;
    }
    if(strcmp(argv[1], "remote") == 0) {
        printf("read remote file\n");
        path = remote_dir;
        if(strcmp(argv[2], "random") == 0) {
            printf("read randomly\n");
            isSequential = 0;
            dat_file = "stat/read_file_dat_remote_radom.txt";
            rst_file = "stat/read_file_rst_remote_radom.txt";
        } else {
            printf("read sequentially\n");
            isSequential = 1;
            dat_file = "stat/read_file_dat_remote_seq.txt";
            rst_file = "stat/read_file_rst_remote_seq.txt";
        }
        start_block_num = 10;
        end_block_num = 410;
        step = 20;
        SIZE_OF_STAT = 10;
        BOUND_OF_LOOP = 10;
    } else {
        //default
        printf("read local file\n");
        path = local_dir;
        if(strcmp(argv[2], "random") == 0) {
            printf("read randomly\n");
            isSequential = 0;
            dat_file = "stat/read_file_dat_local_radom.txt";
            rst_file = "stat/read_file_rst_local_radom.txt";

        } else {
            printf("read sequentially\n");
            isSequential = 1;
            dat_file = "stat/read_file_dat_local_seq.txt";
            rst_file = "stat/read_file_rst_local_seq.txt";
        }
        start_block_num = 10;
        end_block_num = 410;
        step = 20;
        SIZE_OF_STAT = 100;
        BOUND_OF_LOOP = 100;
    }

    FILE *dat_fd = fopen(dat_file, "w");
    if(!dat_fd) {
        printf("open dat file failed\n");
        return -1;
    }

    FILE *rst_fd = fopen(rst_file, "w");
    if(!rst_fd) {
        printf("open rst file failed\n");
        return -1;
    }


    char file[256];
    sprintf(file, "%s/%s", path, filename);

    int fd = open(file, O_RDONLY);
    if(!fd) {
        printf("open %s failed", file);
        return -1;
    }

    for(int block_num = start_block_num; block_num <= end_block_num; block_num+=step) {
        int data_size = BLOCK_SIZE * block_num;
        printf("====================== test for data_size %d (%d)==================\n", data_size, block_num);
        //*================================
        //* open file & generate idx array
        //*================================

        

        int* idx_array = malloc(block_num * sizeof(int));
        for(int i = 0; i < block_num; i++) {
                idx_array[i] = i;
        }
        if(isSequential == 0) {
            shuffle(idx_array, block_num);
        }


        //*=========================== 
        //* allocate memory 
        //*===========================
        uint64_t **time; // store #BOUND_OF_LOOP * SIZE_OF_STAT "time"
        time = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
        if(!time) {
            printf("failed to allocate memory to times...\n");
            return -1;
        }

        for(int i = 0; i <= BOUND_OF_LOOP; i++) {
            time[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
            if(!time[i]) {
                printf("failed to allocate memory to times[%d]...\n", i);
                for(int j = 0; j < i; j++) free(time[j]);
                return -1;
            }
        }

        char buf[BLOCK_SIZE];

        unsigned cycles_high, cycles_low;
        unsigned cycles_high1, cycles_low1;
        uint64_t start, end;
        //*================================
        //* measure read file time
        //*================================
        for(int i = 0; i <= BOUND_OF_LOOP; i++) {
            for(int j = 0; j < SIZE_OF_STAT; j++) {
                unsigned t_sum = 0;
                for(int idx = 0; idx < block_num; idx++) {
                    int pos_idx = idx_array[idx];
                    lseek(fd, pos_idx * BLOCK_SIZE, SEEK_SET);
                     __asm__ __volatile__ ("CPUID\n\t"
                                        "RDTSC\n\t"
                                        "mov %%edx, %0\n\t"
                                        "mov %%eax, %1\n\t"
                                        : "=r" (cycles_high), "=r" (cycles_low)
                                        :: "%rax", "%rbx", "%rcx", "%rdx");
                    read(fd, buf, BLOCK_SIZE);
                    __asm__ __volatile__ ("RDTSC\n\t"
                                            "mov %%edx, %0\n\t"
                                            "mov %%eax, %1\n\t"
                                            "CPUID\n\t"
                                            : "=r" (cycles_high1), "=r" (cycles_low1)
                                            :: "%rax", "%rbx", "%rcx", "%rdx");
                    start = ((uint64_t) cycles_high << 32) | cycles_low;
                    end = ((uint64_t) cycles_high1 << 32) | cycles_low1;
                    if((end - start) < 0) {
                        printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                    } else {
                        t_sum += end - start;
                    }
                    posix_fadvise(fd, pos_idx * BLOCK_SIZE, BLOCK_SIZE, POSIX_FADV_DONTNEED);
                }
                
                time[i][j] = t_sum;
            }
        }
        

        //* =============================
        //* do calculation
        //*==============================
        double mean = 0;
        double variance = 0;
        double variance_of_mean = 0;
        uint64_t max_deviation = 0;
        do_calculation(time + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, rst_file);

        printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
        printf("mean:%.2f\n", mean);
        printf("variance:%.2f\n", variance);
        printf("variance of mean:%.2f\n", variance_of_mean);
        printf("maximum deviation:%lu\n", max_deviation);
        printf("mean speed:%f\n", BLOCK_SIZE * block_num / (mean / mhz));

        fprintf(dat_fd, "%d %d %.2f\n", block_num, block_num*4096, mean);
        for(int i = 0; i < BOUND_OF_LOOP; i++) {
            free(time[i]);
        }

        free(time);

        free(idx_array);
    }
    
    close(fd);
    fclose(dat_fd);
    fclose(rst_fd);
    return 0;
}