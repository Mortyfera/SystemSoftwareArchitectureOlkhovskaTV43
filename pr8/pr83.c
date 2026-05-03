#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define SIZE 50000

int cmp_int(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    return (x > y) - (x < y);
}

double get_time_ms() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000.0 + t.tv_nsec / 1e6;
}

void gen_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void gen_reverse(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void gen_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand();
}

void gen_equal(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = 42;
}

void gen_few_unique(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 5;
}

void run_test(void (*gen)(int*, int), const char *name) {
    int *arr = malloc(sizeof(int) * SIZE);
    gen(arr, SIZE);

    double start = get_time_ms();
    qsort(arr, SIZE, sizeof(int), cmp_int);
    double end = get_time_ms();

    printf("%-20s : %.2f ms\n", name, end - start);

    free(arr);
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++)
        if (arr[i-1] > arr[i]) return 0;
    return 1;
}

void correctness_tests() {
    int test1[] = {5, 3, 1, 4, 2};
    int test2[] = {1, 1, 1, 1};
    int test3[] = {9};
    int test4[] = {2, -1, 0, 5, 3};

    int *tests[] = {test1, test2, test3, test4};
    int sizes[] = {5, 4, 1, 5};

    for (int i = 0; i < 4; i++) {
        qsort(tests[i], sizes[i], sizeof(int), cmp_int);
        printf("Test %d: %s\n", i+1,
               is_sorted(tests[i], sizes[i]) ? "OK" : "FAIL");
    }
}

int main() {
    srand(time(NULL));

    printf("Performance tests:\n\n");

    run_test(gen_random,       "Random");
    run_test(gen_sorted,       "Sorted");
    run_test(gen_reverse,      "Reverse");
    run_test(gen_equal,        "All equal");
    run_test(gen_few_unique,   "Few unique");

    printf("\nCorrectness tests:\n\n");
    correctness_tests();

    return 0;
}