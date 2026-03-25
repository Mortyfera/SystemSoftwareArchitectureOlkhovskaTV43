#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 50000;
    int xb = 50000;
    
    int num = xa * xb;

    printf("xa = %d\n", xa);
    printf("xb = %d\n", xb);
    printf("num (int) = %d\n", num);
    printf("num (size_t) = %zu\n\n", (size_t)num);

    void *ptr = malloc(num);
    
    if (ptr == NULL) {
        printf("malloc повернув NULL\n");
    } else {
        printf("malloc виділив пам'ять\n");
        free(ptr);
    }

    return 0;
}