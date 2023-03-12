#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../utils/calculation.h"

#define BOUND_OF_LOOP 3
#define SIZE_OF_STAT 5
#define ULL unsigned long long
#define xGB(x) ((ULL)x * 1024 * 1024 * 1024)
#define BLOCKSIZE 4096
#define MIN_SIZE xGB(10)
#define MAX_SIZE xGB(14)
#define SIZE_STRIDE xGB(1)


// warm up file buffer cache, read from the end
void warmup(FILE *fd, char *buffer, ULL size) {
    fseek(fd, size - 1, SEEK_SET);
    while(1) {
        fseek(fd, -BLOCKSIZE, SEEK_CUR);
        size_t readn = fread(buffer, BLOCKSIZE, 1, fd);
        if (readn != BLOCKSIZE) {
            break;
        }
    }
}

// return the cycles required for reading a file of size **size**
uint64_t readFile(FILE *fd, char *buffer, ULL size) {
    warmup(fd, buffer, size);
    fseek(fd, 0, SEEK_SET);
    unsigned cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    ULL blockn = size / BLOCKSIZE;
    __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
    
    for (ULL i = 0; i < blockn; i += 4) {
        fread(buffer, BLOCKSIZE, 1, fd);
        fread(buffer, BLOCKSIZE, 1, fd);
        fread(buffer, BLOCKSIZE, 1, fd);
        fread(buffer, BLOCKSIZE, 1, fd);
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
    return end - start;
}

int main () {
    FILE *fd = fopen("/media/stevie/SSD1/testfile", "r"); // a 20GB file
    if(!fd) {
        printf("open file failed\n");
        return -1;
    }
    char *buffer = malloc(BLOCKSIZE * sizeof(char));
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;

    uint64_t **times; // store #BOUND_OF_LOOP * SIZE_OF_STAT "time"
    times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!times) {
        printf("failed to allocate memory to times...\n");
        return -1;
    }

    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        times[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!times[i]) {
            printf("failed to allocate memory to times[%d]...\n", i);
            for(int k = 0; k < i; k++) free(times[k]);
            return -1;
        }
    }

    for (ULL size = MIN_SIZE; size <= MAX_SIZE; size += SIZE_STRIDE) {
        ULL blockn = size / BLOCKSIZE;
        for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
            for (int j = 0; j < SIZE_OF_STAT; j += 1) {
                times[i][j] = readFile(fd, buffer, size) / blockn;
                if (times[i][j] < 0) {
                    printf("wrong time\n");
                    times[i][j] = 0;
                }
            }
        }
        
        char* filename = malloc(50 * sizeof(char));
        sprintf(filename, "../stat/measure_filecache_%lluGB", size / xGB(1));
        do_calculation(times + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);
        printf("====================== Statistics of Reading %llu GB file ==================\n", size / xGB(1));
        printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
        printf("mean per block:%.2f\n", mean);
        printf("variance:%.2f\n", variance);
        printf("variance of mean:%.2f\n", variance_of_mean);
        printf("maximum deviation:%lu\n", max_deviation);
    }

    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        free(times[i]);
    }
    free(times);
    return 0;
}

