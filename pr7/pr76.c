#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_DIRS 1024

int compare(const void *a, const void *b) {
    char *dir1 = *(char **)a;
    char *dir2 = *(char **)b;
    return strcmp(dir1, dir2);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    char *dirs[MAX_DIRS];
    int count = 0;

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

        if (S_ISDIR(statbuf.st_mode)) {
            dirs[count] = strdup(entry->d_name);
            count++;
        }
    }

    closedir(dir);

    qsort(dirs, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}