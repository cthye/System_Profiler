#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "../utils/constant.h"
#include "../utils/calculation.h"

#define PORT 8080
#define SIZE_OF_STAT 100 // inner loop
#define BOUND_OF_LOOP 100 // outer loop

double mhz() {
    printf("====== Measuring CPU frequency ======\n");
    double rate;
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
    rate = (end - start) / (1e6 * 2);
    printf("Running on a %.2f Mhz CPU\n", rate);
    return rate;
}

int main() {
    struct sockaddr_in server_addr;
    int client_sd, status, nread;
    char buffer[1024] = {'0'};
    char *message = "T";
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    unsigned int cycles_low2, cycles_high2, cycles_low3, cycles_high3;
    uint64_t start, end;
    uint64_t **rst_setup;
    uint64_t **rst_close;
    rst_setup = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!rst_setup) {
        printf("failed to allocate memory to rst_setup...\n");
        return 0;
    }
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        rst_setup[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!rst_setup[i]) {
            printf("failed to allocate memory to rst_close[%d]...\n", i);
            for(int k = 0; k < i; k++) free(rst_setup[k]);
            return 0;
        }
    }
    rst_close = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!rst_close) {
        printf("failed to allocate memory to rst_close...\n");
        return 0;
    }
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        rst_close[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!rst_close[i]) {
            printf("failed to allocate memory to rst_close[%d]...\n", i);
            for(int k = 0; k < i; k++) free(rst_close[k]);
            return 0;
        }
    }
    double Mhz = mhz();

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("convert failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            // AF_INET: local communication, SOCK_STREAM: TCP, 0: IP protocol
            if ((client_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                perror("create socket failed");
                exit(EXIT_FAILURE);
            }
            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            if ((status = connect(client_sd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
                perror("connect failed");
                exit(EXIT_FAILURE);
            }
            __asm__ volatile (
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );

            if (send(client_sd, message, strlen(message), 0) < 0) {
                perror("send failed");
                exit(EXIT_FAILURE);
            }
            if (recv(client_sd, buffer, sizeof(buffer), 0) < 0) {
                perror("receive failed");
                exit(EXIT_FAILURE);
            }

            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                rst_setup[i][j] = 0;
            } else {
                rst_setup[i][j] = end - start;
            }

            __asm__ volatile (
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high2), "=r" (cycles_low2)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            close(client_sd);
            __asm__ volatile (
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high3), "=r" (cycles_low3)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );

            start = (((uint64_t)cycles_high2 << 32) | cycles_low2);
            end = (((uint64_t)cycles_high3 << 32) | cycles_low3);
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                rst_close[i][j] = 0;
            } else {
                rst_close[i][j] = end - start;
            }
        }
    }
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char* filename_setup = "../stat/rrt_rst_setup.txt";
    do_calculation(rst_setup + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename_setup);
    
    printf("=========== Setup Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.5f ms\n", mean / Mhz / 1000);
    printf("variance:%.5f ms\n", variance / Mhz / 1000);
    printf("variance of mean:%.5f ms\n", variance_of_mean / Mhz / 1000);
    printf("maximum deviation:%lu\n", max_deviation);

    char* filename_close = "../stat/rrt_rst_close.txt";
    do_calculation(rst_close + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename_close);

    printf("=========== Close Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.5f ms\n", mean / Mhz / 1000);
    printf("variance:%.5f ms\n", variance / Mhz / 1000);
    printf("variance of mean:%.5f ms\n", variance_of_mean / Mhz / 1000);
    printf("maximum deviation:%lu\n", max_deviation);
    
    exit(EXIT_SUCCESS);
}