#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int id;
    double data;
};

int main() {
    struct sbar *ptr, *newptr;

    printf("calloc(1000, sizeof(struct sbar));\n");
    ptr = calloc(1000, sizeof(struct sbar));
    
    if (ptr == NULL) {
        printf("Помилка: calloc не зміг виділити пам'ять.\n");
        return 1;
    }
    printf("calloc успішно виділив пам'ять\n");

    printf("\nreallocarray(ptr, 500, sizeof(struct sbar));\n");
    newptr = reallocarray(ptr, 500, sizeof(struct sbar));

    if (newptr == NULL) {
        printf("Помилка: reallocarray не зміг змінити розмір.\n");
        free(ptr); 
        return 1;
    }

    ptr = newptr;
    printf("reallocarray успішно змінив розмір масиву\n");

    free(ptr);
    ptr = NULL;

    return 0;
}