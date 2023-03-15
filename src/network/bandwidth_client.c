#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory.h>
#include <arpa/inet.h>


#include "../utils/calculation.h"
#include "../utils/constant.h"

const char* dat_file = "stat/net_bandwidth.txt";
// const char* SERVER_IP = "127.0.0.1";
const char* SERVER_IP = "172.20.3.211";

int PORT = 8088;
double mhz;


int main(int argc, char *argv[]) {
    mhz = calc_mhz();
    //*================================
    //* set up dat file
    //*================================
    FILE *dat_fd = fopen(dat_file, "w");
    if(!dat_fd) {
        printf("open dat file failed");
        return -1;
    }
    
    //*================================
    //* set up client
    //*================================
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("create socket failed");
        exit(-1);
    }

    //* server side
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(SERVER_IP);
    sin.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("connection failed");
        exit(-1);
    }


    for(int k = 8; k <= 12; k++) {
        int data_size = (1 << k);
        printf("====================== test for data_size %d ==================\n", data_size);
        //*=========================== 
        //* allocate memory 
        //*===========================
        uint64_t **net_bandwidth; // store #BOUND_OF_LOOP * SIZE_OF_STAT "time"
        net_bandwidth = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*)); // omit the first batch for warm cache
        if(!net_bandwidth) {
            printf("failed to allocate memory to times...\n");
            return -1;
        }

        for(int i = 0; i <= BOUND_OF_LOOP; i++) {
            net_bandwidth[i] = malloc(SIZE_OF_STAT * sizeof(uint64_t));
            if(!net_bandwidth[i]) {
                printf("failed to allocate memory to times[%d]...\n", i);
                for(int j = 0; j < i; j++) free(net_bandwidth[j]);
                return -1;
            }
        }

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

        unsigned cycles_high, cycles_low;
        unsigned cycles_high1, cycles_low1;
        uint64_t start, end;
        double sum = 0;

        //*================================
        //* measure network bandwidth
        //*================================
        for(int i = 0; i <= BOUND_OF_LOOP; i++) {
            for(int j = 0; j < SIZE_OF_STAT; j++) {
                
                char* data = malloc(data_size);
                memset(data, 1, sizeof(data_size));
                
                __asm__ __volatile__ ("CPUID\n\t"
                                        "RDTSC\n\t"
                                        "mov %%edx, %0\n\t"
                                        "mov %%eax, %1\n\t"
                                        : "=r" (cycles_high), "=r" (cycles_low)
                                        :: "%rax", "%rbx", "%rcx", "%rdx");
                send(sock, data, data_size, 0);
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
                    // MB/s
                    net_bandwidth[i][j] = (int)(data_size / ((end - start) / mhz));
                    // net_bandwidth[i][j] = end - start;
                    time[i][j] = end - start;
                }
                free(data);
            }
        }

        //* =============================
        //* do calculation
        //*==============================
        double mean = 0;
        double variance = 0;
        double variance_of_mean = 0;
        uint64_t max_deviation = 0;
        do_calculation(net_bandwidth + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean, &variance, &variance_of_mean, &max_deviation, dat_file);

        double mean1 = 0;
        double variance1 = 0;
        double variance_of_mean1 = 0;
        uint64_t max_deviation1 = 0;
        do_calculation(time + 1, BOUND_OF_LOOP, SIZE_OF_STAT, &mean1, &variance1, &variance_of_mean1, &max_deviation1, dat_file);

        printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
        printf("mean:%.2f\n", mean);
        printf("variance:%.2f\n", variance);
        printf("variance of mean:%.2f\n", variance_of_mean);
        printf("maximum deviation:%lu\n", max_deviation);
        // printf("mean bandwdith:%.2f\n", data_size / (mean / mhz));

        printf("batch size: %d, size of statistic: %d\n", BOUND_OF_LOOP, SIZE_OF_STAT);
        printf("mean:%.2f\n", mean1);
        printf("variance:%.2f\n", variance1);
        printf("variance of mean:%.2f\n", variance_of_mean1);
        printf("maximum deviation:%lu\n", max_deviation1);
        printf("mean bandwdith:%.2f\n", data_size / (mean1 / mhz));

        
        
        // fprintf(dat_fd, "%d %.2f\n", page_num, mean);

        for(int i = 0; i < BOUND_OF_LOOP; i++) {
            free(net_bandwidth[i]);
        }

        free(net_bandwidth);

        for(int i = 0; i < BOUND_OF_LOOP; i++) {
            free(time[i]);
        }

        free(time);

    }
    close(sock);
    return 0;
}