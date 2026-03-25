#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int n = 100;

    for (int i = 1; i <= 2; i++) {
        printf("Ітерація %d\n", i);
        
        if (!ptr) {
            ptr = malloc(n);
            printf("Пам'ять виділено за адресою: %p\n", ptr);
        } else {
            printf("ptr не NULL (%p), malloc пропущено\n", ptr);
        }

        // [... використання 'ptr' ...]
        printf("Використання ptr...\n");

        free(ptr);
        printf("Пам'ять звільнено.\n\n");
    }

    return 0;
}