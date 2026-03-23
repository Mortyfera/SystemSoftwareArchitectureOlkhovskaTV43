#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void handle_file_size_limit(int signal_number) {
    printf("\nПомилка: Перевищено ліміт розміру файлу під час копіювання.\n");
    exit(1);
}

int main(int argument_count, char *arguments[]) {

    if (argument_count != 3) {
        printf("Для роботи програми порібно передати два аргументи.\n");
        return 1;
    }

    signal(SIGXFSZ, handle_file_size_limit);

    char *source_filename = arguments[1];
    char *destination_filename = arguments[2];

    int source_file = open(source_filename, O_RDONLY);
    if (source_file < 0) {
        printf("Неможливо відкрити файл %s для читання\n", source_filename);
        return 1;
    }

    int destination_file = open(destination_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination_file < 0) {
        printf("Неможливо відкрити файл %s для запису\n", destination_filename);
        close(source_file); 
        return 1;
    }

    char data_buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(source_file, data_buffer, sizeof(data_buffer))) > 0) {
        
        write(destination_file, data_buffer, bytes_read);
    }

    printf("Файл успішно скопійовано.\n");
    close(source_file);
    close(destination_file);
    
    return 0;
}