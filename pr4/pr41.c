#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

int main() {
    printf("Характеристики архітектури\n");
    printf("Розмір вказівника (void*): %zu байтів (%zu біт)\n", sizeof(void*), sizeof(void*) * 8);
    printf("Розмір size_t: %zu байтів\n", sizeof(size_t));
    printf("Розмір ptrdiff_t: %zu байтів\n\n", sizeof(ptrdiff_t));

    printf("Теоретичні ліміти\n");
    printf("SIZE_MAX (повний простір, 16 ЕБ / 4 ГБ): %llu байтів\n", (unsigned long long)SIZE_MAX);
    printf("PTRDIFF_MAX (ліміт масиву, 8 ЕБ / 2 ГБ): %llu байтів\n\n", (unsigned long long)PTRDIFF_MAX);

    printf("Виділяємо пам'ять\n");
    printf("Пробуємо malloc(SIZE_MAX)...\n");
    void *ptr1 = malloc(SIZE_MAX);
    if (ptr1 == NULL) {
        printf("Помилка: ОС відмовила у виділенні SIZE_MAX байтів.\n");
    } else {
        printf("Не має ввивестись\n");
        free(ptr1);
    }

    printf("Пробуємо malloc(PTRDIFF_MAX)...\n");
    void *ptr2 = malloc(PTRDIFF_MAX);
    if (ptr2 == NULL) {
        printf("Помилка: ОС відмовила у виділенні PTRDIFF_MAX байтів.\n");
    } else {
        printf("Не має вивестись\n");
        free(ptr2);
    }

    return 0;
}