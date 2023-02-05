#ifndef CYCLECTR_HEADER
#define CYCLECTR_HEADER
#include <stdint.h>

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));
    return ((uint64_t) hi << 32) | lo;
}

#endif