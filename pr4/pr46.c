#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("realloc(NULL, size)\n");
    
    int *ptr = realloc(NULL, 3 * sizeof(int));
    
    if (ptr != NULL) {
        printf("realloc спрацював як malloc.\n");
        printf("Пам'ять виділено за адресою: %p\n", (void*)ptr);
    } else {
        printf("Помилка виділення пам'яті.\n\n");
        return 1;
    }

    printf("realloc(ptr, 0)\n");
    
    void *new_ptr = realloc(ptr, 0);
    
    if (new_ptr == NULL) {
        printf("realloc(ptr, 0) повернув NULL.\n");
        printf("Пам'ять за адресою %p було звільнено.\n", (void*)ptr);
    } else {
        printf("Пам'ять звільнено, але повернуто вказівник: %p\n", new_ptr);
        free(new_ptr); 
    }

    ptr = NULL; 

    return 0;
}