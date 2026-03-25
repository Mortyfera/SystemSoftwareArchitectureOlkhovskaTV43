#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_maps(const char *stage) {
    printf("\n--- /proc/self/maps (%s) ---\n", stage);
    char cmd[256];
    
    sprintf(cmd, "cat /proc/%d/maps | grep -E 'heap|rw-p'", getpid()); 
    
    system(cmd); 
    printf("\n\n");
}

int main() {
    print_maps("СТАРТ: Чиста пам'ять");

    size_t large_size = 200 * 1024 * 1024;
    void *large_ptr = malloc(large_size);
    printf("\nВиділено великий блок: 200 МБ за адресою %p\n", large_ptr);
    print_maps("ПІСЛЯ ВИДІЛЕННЯ БЛОКУ 200 МБ");
    
    free(large_ptr);
    print_maps("ПІСЛЯ ЗВІЛЬНЕННЯ БЛОКУ 200 МБ");

    int num_blocks = 200000;
    void **small_ptrs = malloc(num_blocks * sizeof(void*));
    
    for (int i = 0; i < num_blocks; i++) {
        small_ptrs[i] = malloc(1024);
    }
    printf("\nВиділено 200 000 блоків по 1 КБ. Останній за адресою: %p\n", small_ptrs[num_blocks-1]);
    print_maps("ПІСЛЯ 200 000 БЛОКІВ ПО 1 КБ");

    for (int i = 0; i < num_blocks; i++) {
        free(small_ptrs[i]);
    }
    free(small_ptrs);

    return 0;
}