#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void list_files(const char *basePath) {
    struct dirent *entry;
    DIR *dir = opendir(basePath);

    if (!dir) {
        perror(basePath);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || 
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);

        struct stat statbuf;
        if (lstat(path, &statbuf) == -1) {
            perror(path);
            continue;
        }

        printf("%s\n", path);

        if (S_ISDIR(statbuf.st_mode)) {
            list_files(path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}