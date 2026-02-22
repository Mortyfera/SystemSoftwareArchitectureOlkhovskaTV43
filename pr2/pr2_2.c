#include <stdio.h>
#include <stdlib.h>

int global_initialized = 95; 

int global_uninitialized;    

void grow_stack() {
    int array[10000]; 
    int stack;
    
    array[0] = 1;

    printf("The stack top inside grow_stack is near %p\n", (void*)&stack);
}

int main() {
    int i; 

    int *heap_ptr = (int *)malloc(sizeof(int)); 

    printf("--- Memory Layout Addresses ---\n");
    printf("Text segment (code) is near  %p\n", (void*)main);
    
    printf("Data segment (initialized) is near  %p\n", (void*)&global_initialized);
    printf("BSS segment (uninitialized) is near %p\n", (void*)&global_uninitialized);
    
    printf("Heap (dynamic data) is near  %p\n", (void*)heap_ptr);
    
    printf("The stack top in main is near      %p\n", (void*)&i);

    grow_stack();

    free(heap_ptr);
    return 0;
}