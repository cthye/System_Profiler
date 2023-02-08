// DON'T USE THIS FILE
#ifndef CYCLECTR_HEADER
#define CYCLECTR_HEADER
#include <stdint.h>

extern inline uint64_t getStartCycle() {
    unsigned cycles_low, cycles_high;
    uint64_t start;
    __asm__ volatile (
    "cpuid\n\t"
    "rdtsc\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    : "=r" (cycles_high), "=r" (cycles_low)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    start = (((uint64_t)cycles_high << 32) | cycles_low);
    return start;
}

extern inline uint64_t getEndCycle() {
    unsigned cycles_low, cycles_high;
    uint64_t end;
    __asm__ volatile(
    "rdtscp\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    "cpuid\n\t": "=r" (cycles_high), "=r" (cycles_low)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    end = (((uint64_t)cycles_high << 32) | cycles_low);
    return end;
}

#endif