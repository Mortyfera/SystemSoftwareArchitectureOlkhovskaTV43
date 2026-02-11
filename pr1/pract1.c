#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 1
#define MAX_SIZE 1000

void print_memory_status(const char* operation, void* ptr, int size) {
    if (ptr != NULL) {
        printf("[LOG] %s is success. Address: %p, Current Size: %d elements (%lu bytes)\n", operation, ptr, size, size * sizeof(int));
    } else {
        printf("[LOG] %s has failed or memory was freed.\n", operation);
    }
}

int* change_array_size(int *arr, int *current_size) {
    int new_size;

    printf("\nEnter new size for the array (%d - %d): ", MIN_SIZE, MAX_SIZE);
    scanf("%d", &new_size);

    if (new_size < MIN_SIZE || new_size > MAX_SIZE) {
        printf("Error. Size must be between %d and %d.\n", MIN_SIZE, MAX_SIZE);
        return arr;
    }

    int *temp = (int*)realloc(arr, new_size * sizeof(int));

    if (temp == NULL) {
        printf("\nError. Unable to reallocate memory.\n");
        return arr;
    } else {
        *current_size = new_size;
        
        print_memory_status("Realloc", temp, new_size);
        
        for (int i = 0; i < new_size; i++) {
            temp[i] = new_size;
        }

        printf("Array resized and refilled:\n");
        for (int i = 0; i < new_size; i++) {
            printf("%d ", temp[i]);
        }
        printf("\n");
        
        return temp;
    }
}

int main() {
    int size;
    int *arr = NULL;
    
    printf("Enter initial size of the dynamic array (%d - %d): ", MIN_SIZE, MAX_SIZE);
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE) {
        printf("Error. Invalid size.\n");
        return 1;
    }
    
    arr = (int*)malloc(size * sizeof(int));
    
    if (arr == NULL) {
        printf("\nError. Memory not allocated.\n");
        return 1;
    }

    print_memory_status("Malloc", arr, size);

    for (int i = 0; i < size; i++) {
        arr[i] = size;
    }

    printf("Initial Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char answer;
    
    printf("\nDo you want to change the size of the existing array (y/n): ");
    scanf(" %c", &answer); 

    while (answer == 'y' || answer == 'Y') {
        arr = change_array_size(arr, &size);
        
        printf("\nDo you want to change the size again (y/n): ");
        scanf(" %c", &answer);
    }

    free(arr);
    arr = NULL;
    print_memory_status("Free", arr, 0);

    return 0;
}