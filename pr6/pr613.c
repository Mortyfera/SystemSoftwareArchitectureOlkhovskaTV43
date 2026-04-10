#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    void *allocations[100];

    for (int i = 0; i < 100; i++) {
        size_t size = 1024 * 1024; //1 МБ
        allocations[i] = malloc(size);

        if (allocations[i] == NULL) {
            fprintf(stderr, "Помилка виділення пам'яті.\n");
            return 1;
        }

        memset(allocations[i], 0, size);

        printf("Ітерація %d: Виділено 1 МБ. Загалом: %d МБ\n", i + 1, i + 1);

        usleep(50000); 
    }

    return 0;
}