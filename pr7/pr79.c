#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>

int main() {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (volatile int i = 0; i < 100000000; i++);

    clock_gettime(CLOCK_MONOTONIC, &end);

    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;

    double elapsed_ms = seconds * 1000.0 + nanoseconds / 1e6;

    printf("Execution time: %.3f ms\n", elapsed_ms);

    return 0;
}