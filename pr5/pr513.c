#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PAGE_SIZE 4096
#define NUMBER_OF_PAGES 25600 // 100 МБ

int main() {
    size_t memory_size = PAGE_SIZE * NUMBER_OF_PAGES;

    printf("1. (Батьківський процес) Виділяю %zu байт (100 МБ) пам'яті\n", memory_size);
    char *buffer = malloc(memory_size);
    if (buffer == NULL) {
        perror("Помилка malloc");
        return 1;
    }

    printf("2. (Батьківський процес) Заповнюю пам'ять нулями\n");
    memset(buffer, 0, memory_size);

    printf("\n(Батьківській процес) PID: %d\n", getpid());
    printf("Натисніть Enter, щоб зробити fork()\n");
    getchar();

    pid_t pid = fork();

    if (pid < 0) {
        perror("Помилка fork()");
        exit(1);
    } 
    else if (pid == 0) {
        printf("\n3. (Дочірній процес) PID: %d\n", getpid());
        printf("Наразі пам'ять дочірнього процесу спільна з батьківським процесом завдяки copy-on-write\n");
        printf("Натисніть Enter, щоб змінити по 1 байту на кожній сторінці\n");
        getchar();

        printf("4. (Дочірній процес) Записую по одному символу 'A' з кроком в 4096 байт\n");
        for (size_t i = 0; i < memory_size; i += PAGE_SIZE) {
            buffer[i] = 'A';
        }

        printf("5. (Дочірній процес) RSS мав різко зрости на 100 МБ.\n");
        printf("Натисніть Enter, щоб завершити програму\n");
        getchar();

        free(buffer);
        exit(0);
    } 
    else {
        wait(NULL);
        free(buffer);
    }

    return 0;
}