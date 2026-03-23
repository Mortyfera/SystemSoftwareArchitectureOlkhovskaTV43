#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/resource.h>

void handle_stack_overflow_error(int signal_number) {
    printf("\nСтек переповнено.\n");
    exit(1);
}

void dive_into_stack(int current_depth) {
    char memory_block[1024]; 
    
    if (current_depth % 100 == 0) {
        printf("Глибина занурення: %d викликів...\n", current_depth);
    }
    
    dive_into_stack(current_depth + 1);
}

int main() {
    stack_t emergency_stack = {
        .ss_sp = malloc(SIGSTKSZ),
        .ss_size = SIGSTKSZ,
        .ss_flags = 0
    };
    sigaltstack(&emergency_stack, NULL);

    struct sigaction signal_action = {0};
    signal_action.sa_handler = handle_stack_overflow_error;
    signal_action.sa_flags = SA_ONSTACK;
    sigaction(SIGSEGV, &signal_action, NULL);

    struct rlimit stack_limit = {1024 * 1024, 1024 * 1024}; 
    setrlimit(RLIMIT_STACK, &stack_limit);

    printf("Обмеження стеку: 1 Мегабайт.\n\n");

    dive_into_stack(1);

    return 0;
}