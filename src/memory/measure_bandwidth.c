#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../utils/calculation.h"
#include "../utils/constant.h"

#define BOUND_OF_LOOP 100
#define N_BYTES (1 << 22) // 4MB
#define N_INTS (N_BYTES >> 2)
#define CACHE_SIZE (1 << 22) // 4MB

char foo[CACHE_SIZE], bar[CACHE_SIZE];
#define OBLIT_CACHE memcpy(foo, bar, CACHE_SIZE)

uint64_t benchmark_read(int* beg, int* end) {
    uint64_t *times;
    times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*));
    if(!times) {
        printf("failed to allocate memory to times...\n");
        return 0;
    }

    uint64_t start_time, end_time;
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t sum = 0;
    uint64_t sum_times = 0;

    for (int i=0; i <= BOUND_OF_LOOP; i=i+1) {
        int *p = beg;
        OBLIT_CACHE;

        __asm__ volatile (
        "cpuid\n\t"
        "rdtsc\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        : "=r" (cycles_high0), "=r" (cycles_low0)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

        while (p < end) {
#define OP(i) sum += p[i];
  OP(0)  OP(8)  OP(16)  OP(24)  OP(32)  OP(40)  OP(48)  OP(56)  OP(64)  OP(72)  OP(80)  OP(88)  OP(96)  OP(104)  OP(112)  OP(120)  OP(128)  OP(136)  OP(144)  OP(152)  OP(160)  OP(168)  OP(176)  OP(184)  OP(192)  OP(200)  OP(208)  OP(216)  OP(224)  OP(232)  OP(240)  OP(248)  OP(256)  OP(264)  OP(272)  OP(280)  OP(288)  OP(296)  OP(304)  OP(312)  OP(320)  OP(328)  OP(336)  OP(344)  OP(352)  OP(360)  OP(368)  OP(376)  OP(384)  OP(392)  OP(400)  OP(408)  OP(416)  OP(424)  OP(432)  OP(440)  OP(448)  OP(456)  OP(464)  OP(472)  OP(480)  OP(488)  OP(496)  OP(504)  OP(512)  OP(520)  OP(528)  OP(536)  OP(544)  OP(552)  OP(560)  OP(568)  OP(576)  OP(584)  OP(592)  OP(600)  OP(608)  OP(616)  OP(624)  OP(632)  OP(640)  OP(648)  OP(656)  OP(664)  OP(672)  OP(680)  OP(688)  OP(696)  OP(704)  OP(712)  OP(720)  OP(728)  OP(736)  OP(744)  OP(752)  OP(760)  OP(768)  OP(776)  OP(784)  OP(792)  OP(800)  OP(808)  OP(816)  OP(824)  OP(832)  OP(840)  OP(848)  OP(856)  OP(864)  OP(872)  OP(880)  OP(888)  OP(896)  OP(904)  OP(912)  OP(920)  OP(928)  OP(936)  OP(944)  OP(952)  OP(960)  OP(968)  OP(976)  OP(984)  OP(992)  OP(1000)  OP(1008)  OP(1016)
p += 1024;
        }

        __asm__ volatile(
        "rdtscp\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );
        
        start_time = (((uint64_t)cycles_high0 << 32) | cycles_low0);
        end_time = (((uint64_t)cycles_high1 << 32) | cycles_low1);
        if((end_time - start_time) < 0) {
            printf("wrong timing: start:%lu, end:%lu ...\n", start_time, end_time);
            times[i] = 0;
        } else {
	    // printf("------------time:%lu\n",end_time-start_time);
            times[i] = end_time - start_time;
        }
    }
    for(int i=0;i<=BOUND_OF_LOOP;i++){
        sum_times=sum_times+times[i];
    }
    // printf("read sum_times: %lld\n",sum_times);
    return (uint64_t)(sum_times / (BOUND_OF_LOOP+1)); // - READING_TIME_OVERHEAD;
}
#undef OP

uint64_t benchmark_write(int* beg, int* end) {

    uint64_t *times;
    times = malloc((BOUND_OF_LOOP + 1)* sizeof(uint64_t*));
    if(!times) {
        printf("failed to allocate memory to times...\n");
        return 0;
    }

    uint64_t start_time, end_time;
    unsigned int cycles_low0, cycles_high0, cycles_low1, cycles_high1;
    uint64_t sum_times = 0;

    for (int i=0; i < BOUND_OF_LOOP; ++i) {
        int *p = beg;
        OBLIT_CACHE;

        __asm__ volatile (
        "cpuid\n\t"
        "rdtsc\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        : "=r" (cycles_high0), "=r" (cycles_low0)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

        while (p < end) {
#define OP(i) p[i] = 1;
  OP(0)  OP(8)  OP(16)  OP(24)  OP(32)  OP(40)  OP(48)  OP(56)  OP(64)  OP(72)  OP(80)  OP(88)  OP(96)  OP(104)  OP(112)  OP(120)  OP(128)  OP(136)  OP(144)  OP(152)  OP(160)  OP(168)  OP(176)  OP(184)  OP(192)  OP(200)  OP(208)  OP(216)  OP(224)  OP(232)  OP(240)  OP(248)  OP(256)  OP(264)  OP(272)  OP(280)  OP(288)  OP(296)  OP(304)  OP(312)  OP(320)  OP(328)  OP(336)  OP(344)  OP(352)  OP(360)  OP(368)  OP(376)  OP(384)  OP(392)  OP(400)  OP(408)  OP(416)  OP(424)  OP(432)  OP(440)  OP(448)  OP(456)  OP(464)  OP(472)  OP(480)  OP(488)  OP(496)  OP(504)  OP(512)  OP(520)  OP(528)  OP(536)  OP(544)  OP(552)  OP(560)  OP(568)  OP(576)  OP(584)  OP(592)  OP(600)  OP(608)  OP(616)  OP(624)  OP(632)  OP(640)  OP(648)  OP(656)  OP(664)  OP(672)  OP(680)  OP(688)  OP(696)  OP(704)  OP(712)  OP(720)  OP(728)  OP(736)  OP(744)  OP(752)  OP(760)  OP(768)  OP(776)  OP(784)  OP(792)  OP(800)  OP(808)  OP(816)  OP(824)  OP(832)  OP(840)  OP(848)  OP(856)  OP(864)  OP(872)  OP(880)  OP(888)  OP(896)  OP(904)  OP(912)  OP(920)  OP(928)  OP(936)  OP(944)  OP(952)  OP(960)  OP(968)  OP(976)  OP(984)  OP(992)  OP(1000)  OP(1008)  OP(1016)
p += 1024;
        }

        __asm__ volatile(
        "rdtscp\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "cpuid\n\t": "=r" (cycles_high1), "=r" (cycles_low1)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );
        
        start_time = (((uint64_t)cycles_high0 << 32) | cycles_low0);
        end_time = (((uint64_t)cycles_high1 << 32) | cycles_low1);
        if((end_time - start_time) < 0) {
            printf("wrong timing: start:%lu, end:%lu ...\n", start_time, end_time);
            times[i] = 0;
        } else {
            // printf("time:%lu\n", end_time - start_time);
            times[i] = end_time - start_time;
        }
    }
    for(int i=0;i<=BOUND_OF_LOOP;i++){
        sum_times=sum_times+times[i];
    }
    //printf("write sum_times: %ld\n",sum_times);
    return (uint64_t)(sum_times / (BOUND_OF_LOOP+1)); // - READING_TIME_OVERHEAD;
}
#undef OP

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
    uint64_t tw, tr;
    int arr[N_INTS];
    double Mhz = mhz();

    tr = benchmark_read(arr, arr + N_INTS);
    tw = benchmark_write(arr, arr + N_INTS);

    // bandwidth: GB/s = GB * cycles/s * 1/cycles
    #define t2b(t) ((N_BYTES/8.0) / (t / Mhz))
    printf("Raw read/write time: %ld, %ld\n",tr,tw);
    printf("Read bandwidth: %.5f (MB/s); Write bandwidth: %.5f (MB/s)\n", t2b(tr), t2b(tw));

    #undef t2b
}