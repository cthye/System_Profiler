#include <stdio.h>
#include <stdlib.h>
#include "../utils/cycle_counter.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("usage : ./program 10");
        exit(0);
    }
    int loops = atoi(argv[1]);

    unsigned long long total = 0;
    unsigned long long start, end;
    int i=0; 
    for(; i < loops; i++) {
	start = rdtsc();
	end = rdtsc();
	total += (end - start);
    }

    printf("CPU's overhead of reading rdtsc: \n ***total time: %llu cycles \n ***average time: %f cycles \n", total, total*1.0/loops);


    
    start = rdtsc();
    i=0;
    for (; i < loops; ++i) {}
    end = rdtsc();
    total = end - start;
    printf ("CPU's overhead of using a loop to measure many iterations of an operation: \n *** total time: %llu cycles \n ***average time: %f cycles \n", total, total*1.0/loops);
    
}
