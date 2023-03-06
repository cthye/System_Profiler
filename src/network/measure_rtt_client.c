#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "../utils/constant.h"
#include "../utils/calculation.h"

#define PORT 8080

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
    char *message = "TAOTAO!TAOTAO!TAOTAO!TAOTAO!TAOTAO!TAOTAO!TAOTAO!TAOTAO";
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t start, end;
    uint64_t **rst;
    rst = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
    if(!rst) {
        printf("failed to allocate memory to rst...\n");
        return 0;
    }
    for(int i = 0; i <= BOUND_OF_LOOP; i++) {
        rst[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
        if(!rst[i]) {
            printf("failed to allocate memory to rst[%d]...\n", i);
            for(int k = 0; k < i; k++) free(rst[k]);
            return 0;
        }
    }
    double Mhz = mhz();
    // AF_INET: local communication, SOCK_STREAM: TCP, 0: IP protocol
    if ((client_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("convert failed");
        exit(EXIT_FAILURE);
    }
    if ((status = connect(client_sd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= BOUND_OF_LOOP; i += 1) {
        for (int j = 0; j < SIZE_OF_STAT; j += 1) {
            __asm__ volatile (
            "cpuid\n\t"
            "rdtsc\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high0), "=r" (cycles_low0)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );

            send(client_sd, message, strlen(message), 0);
            read(client_sd, buffer, 1024);

            __asm__ volatile (
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
            start = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            end = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            if((end - start) < 0) {
                printf("wrong timing: start:%lu, end:%lu ...\n", start, end);
                rst[i][j] = 0;
            } else {
                rst[i][j] = end - start;
            }
        }
    }
    double mean = 0;
    double variance = 0;
    double variance_of_mean = 0;
    uint64_t max_deviation = 0;
    char* filename = "../stat/rrt_rst.txt";
    do_calculation(rst + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, filename);

    printf("=========== Statistics ===========\n");
    printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
    printf("mean:%.5f ms\n", mean / Mhz / 1000);
    printf("variance:%.5f ms\n", variance / Mhz / 1000);
    printf("variance of mean:%.5f ms\n", variance_of_mean / Mhz / 1000);
    printf("maximum deviation:%lu\n", max_deviation);
    close(client_sd);
    exit(EXIT_SUCCESS);
}