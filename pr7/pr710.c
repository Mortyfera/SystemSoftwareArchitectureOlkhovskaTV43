#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int count;
    float n;

    srand(time(NULL));

    printf("Enter number of random values: ");
    scanf("%d", &count);

    printf("Enter n (upper bound for range [0, n]): ");
    scanf("%f", &n);

    printf("\nRandom numbers in range [0.0, 1.0]:\n");
    for (int i = 0; i < count; i++) {
        float r = (float)rand() / RAND_MAX;
        printf("%f\n", r);
    }

    printf("\nRandom numbers in range [0.0, %.2f]:\n", n);
    for (int i = 0; i < count; i++) {
        float r = ((float)rand() / RAND_MAX) * n;
        printf("%f\n", r);
    }

    return 0;
}