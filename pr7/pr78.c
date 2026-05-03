#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    int delete_all = 0;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (!S_ISREG(statbuf.st_mode))
            continue;

        if (!delete_all) {
            printf("Delete file '%s'? (y/n/a/q): ", entry->d_name);

            char answer;
            scanf(" %c", &answer);

            if (answer == 'q' || answer == 'Q') {
                break;
            } else if (answer == 'a' || answer == 'A') {
                delete_all = 1;
            } else if (answer == 'n' || answer == 'N') {
                continue;
            } else if (answer != 'y' && answer != 'Y') {
                printf("Unknown option, skipped.\n");
                continue;
            }
        }

        if (remove(entry->d_name) == 0) {
            printf("Deleted: %s\n", entry->d_name);
        } else {
            perror(entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}