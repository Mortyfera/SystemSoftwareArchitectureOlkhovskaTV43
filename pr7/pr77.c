#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int has_c_extension(const char *name) {
    const char *dot = strrchr(name, '.');
    return dot && strcmp(dot, ".c") == 0;
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    printf("C source files:\n\n");

    while ((entry = readdir(dir)) != NULL) {
        if (!has_c_extension(entry->d_name))
            continue;

        if (stat(entry->d_name, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (!S_ISREG(statbuf.st_mode))
            continue;

        printf("File: %s\n", entry->d_name);
        printf("Allow others to read this file? (y/n): ");

        char answer;
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            mode_t new_mode = statbuf.st_mode | S_IROTH;

            if (chmod(entry->d_name, new_mode) == -1) {
                perror("chmod");
            } else {
                printf("Read permission for others added.\n");
            }
        } else {
            printf("Skipped.\n");
        }

        printf("\n");
    }

    closedir(dir);
    return 0;
}