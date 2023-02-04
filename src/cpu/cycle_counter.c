#include <stdint.h>
#include <stdio.h>

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t) hi << 32) | lo;
}

int main() {
    for(int i = 0; i < 10; i++) {
        uint64_t t1 = rdtsc();
        sleep(1);
        uint64_t t2 = rdtsc();
        printf("%d: %lu\n", i, t2 - t1);
    }
}