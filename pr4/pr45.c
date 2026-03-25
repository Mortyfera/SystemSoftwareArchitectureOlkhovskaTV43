#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int *ptr = malloc(10 * sizeof(int));
    if (ptr == NULL) {
        printf("Помилка, пам'ять не була виділена.\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        ptr[i] = i * 10;
    }
    for (int i = 0; i < 10; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    
    int *temp_ptr = realloc(ptr, SIZE_MAX);

    if (temp_ptr == NULL) {
        printf("realloc повернув NULL. пам'ять не було виділено.\n");
        printf("Перевірка цілісності старої ділянки пам'яті:\n");
        for (int i = 0; i < 10; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
        free(ptr);
    } else {
        printf("realloc спрацював\n");
        ptr = temp_ptr;
        free(ptr);
    }

    return 0;
}