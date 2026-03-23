#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <signal.h>

void handle_file_size_limit_error(int signal_number) {
    printf("\nФайл досяг максимального розміру! Зупинка алгоритму.\n");
    exit(0); 
}

int main() {
    signal(SIGXFSZ, handle_file_size_limit_error);

    struct rlimit file_size_limit = {50, 50}; 
    setrlimit(RLIMIT_FSIZE, &file_size_limit);

    FILE *output_file = fopen("dice_rolls.txt", "w");
    
    setvbuf(output_file, NULL, _IONBF, 0); 

    int dice_roll_count = 1;
    
    while (1) {
        fprintf(output_file, "Кидок %d: %d\n", dice_roll_count, rand() % 6 + 1);
        
        printf("Записано кидок %d\n", dice_roll_count);
        
        dice_roll_count++;
    }

    return 0; 
}