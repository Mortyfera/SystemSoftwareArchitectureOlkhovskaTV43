#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int n = 100;

    for (int i = 1; i <= 2; i++) {
        if (!ptr) {
            ptr = malloc(n);
        }

        // [... використання 'ptr' ...]

        free(ptr);
        ptr = NULL;
    }

    return 0;
}