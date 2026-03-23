#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <signal.h>

long long total_tickets_generated = 0;

void handle_cpu_limit_reached(int signal_number) {
    printf("\nЧас вийшов. Ліміт процесорного часу вичерпано.\n");
    printf("Встигли згенерувати білетів: %lld\n", total_tickets_generated);
    exit(0);
}

void generate_lotto_numbers(int numbers_to_pick, int max_number, int *ticket_array) {
    for (int i = 0; i < numbers_to_pick; i++) {
        int new_number, is_unique;
        do {
            new_number = rand() % max_number + 1;
            is_unique = 1;
            
            for (int j = 0; j < i; j++) {
                if (ticket_array[j] == new_number) {
                    is_unique = 0;
                    break;
                }
            }
        } while (!is_unique);
        
        ticket_array[i] = new_number;
    }
}

int main() {
    signal(SIGXCPU, handle_cpu_limit_reached);

    struct rlimit cpu_time_limit = {1, 2}; 
    setrlimit(RLIMIT_CPU, &cpu_time_limit);

    printf("Обмеження: 1 секунда чистого процесорного часу. Генерація починається...\n\n");

    int lotto_7_49[7];
    int lotto_6_36[6];

    while (1) {
        generate_lotto_numbers(7, 49, lotto_7_49);
        generate_lotto_numbers(6, 36, lotto_6_36);
        
        total_tickets_generated++;

        if (total_tickets_generated % 100000 == 0) {
            printf("Згенеровано %lld білетів...\n", total_tickets_generated);
        }
    }

    return 0;
}