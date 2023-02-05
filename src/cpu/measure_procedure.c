#include <stdio.h>
#include <unistd.h>

#include "../utils/cycle_counter.h"
#define iter 10

int main() {
    for (int i = 0; i < iter; i += 1) {
        uint64_t start = rdtsc();
        sleep(1);
        uint64_t end = rdtsc();
        printf("ITER[%d] %lu\n", i, end - start);
    }
}