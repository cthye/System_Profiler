#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "../utils/calculation.h"
// #include "../utils/constant.h"

const int SIZE_OF_STAT = 100; // #inner loop
const int BOUND_OF_LOOP = 100; // #outer loop
const int PAGE_SIZE = 4096;
// const char* dir = "/media/cthye/Cthye/221";
const char* dir = "/media/cthye/Cthye/221-prime";
// const char* dat = "./stat/page_fault_dat.txt";
const char* dat = "./stat/page_fault_dat2.txt";




void run(int size, int page_num, FILE* dat_fd) {
    printf("start measuring...\n");
    

    //*=========================== 
    //* allocate memory 
    //*===========================
    uint64_t **page_fault_times; // store #BOUND_OF_LOOP * SIZE_OF_STAT "time"
    page_fault_times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!page_fault_times) {
        printf("failed to allocate memory to times...\n");
        return;
    }

    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        page_fault_times[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!page_fault_times[i]) {
            printf("failed to allocate memory to times[%d]...\n", i);
            for(int k = 0; k < i; k++) free(page_fault_times[k]);
            return;
        }
    }

    //*==========================
    //* open file
    //*==========================
    char mmap_file[100];
    sprintf(mmap_file, "%s/%d", dir, size);
    int fd;
    if((fd=open(mmap_file, O_RDONLY)) < 0) {
        printf("failed to open file[%s]...\n", mmap_file);
        return;
    }

    unsigned cycles_high, cycles_low;
    unsigned cycles_high1, cycles_low1;
    uint64_t start, end;
    uint64_t sum = 0;
    //*================================
    //* measure page fault overhead
    //*================================
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        for(int j = 0; j < SIZE_OF_STAT; j++) {
            __asm__ __volatile__ ("CPUID\n\t"
                                    "RDTSC\n\t"
                                    "mov %%edx, %0\n\t"
                                    "mov %%eax, %1\n\t"
                                    : "=r" (cycles_high), "=r" (cycles_low)
                                    :: "%rax", "%rbx", "%rcx", "%rdx");
            //* page fault: using mmap to measure major page fault
            //* using shared buffer can avoid copying data from kernel space back-and-from to user space
            //* notice that kernel would support file buffer read-ahead to optimize reading cost
            char* map = (char*) mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
            // posix_madvise(map, size, POSIX_MADV_RANDOM);
            //? overhead
            if(map == MAP_FAILED) {
                printf("failed to mmap to file:%s\n", mmap_file);
                return;
            }
            for(int k = 0; k < size; k++) {
                sum += map[k];
            }
            __asm__ __volatile__ ("RDTSC\n\t"
                                    "mov %%edx, %0\n\t"
                                    "mov %%eax, %1\n\t"
                                    "CPUID\n\t"
                                    : "=r" (cycles_high1), "=r" (cycles_low1)
                                    :: "%rax", "%rbx", "%rcx", "%rdx");
            munmap(map, size);
            start = ((uint64_t) cycles_high << 32) | cycles_low;
            end = ((uint64_t) cycles_high1 << 32) | cycles_low1;
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
            } else {
                //* overhead per page
                page_fault_times[i][j]= (end - start) / page_num;
            }
        }
    }

    //* =============================
    //* do calculation
    //*==============================
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char filename[256];
    sprintf(filename, "stat/page_fault_%d.txt", page_num);
    do_calculation(page_fault_times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("====================== page fault ==================\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.2f\n", mean);
    printf("variance:%.2f\n", variance);
    printf("variance of mean:%.2f\n", variance_of_mean);
    printf("maximum deviation:%lu\n", max_deviation);

    double disk_speed = get_throughput(PAGE_SIZE, 1, mean);
    printf("disk transfer rate: %.2f\n", disk_speed);

    
    fprintf(dat_fd, "%d %.2f\n", page_num, mean);

    for(int i = 0; i < BOUND_OF_LOOP; i++) {
        free(page_fault_times[i]);
    }

    free(page_fault_times);
    return;
}

int main(int argc, char *argv[]) {
    //todo
    FILE *dat_fd = fopen(dat, "w");
    if(!dat_fd) {
        printf("open dat file failed");
        return -1;
    }
    for(int i = 1; i <= 30; i++) {
        int size = PAGE_SIZE * i * 100;
        printf("====================== test for size %d (%d pages) ==================\n", size, i * 100);
        run(size, i * 100, dat_fd);
    }
    return 0;
}