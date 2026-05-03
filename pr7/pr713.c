#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

int is_executable(mode_t mode) {
    return (mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH);
}

int is_suspicious_permissions(mode_t mode) {
    return (mode & S_IWOTH) && (mode & S_IXOTH);
}

int is_valid_executable(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return 0;

    unsigned char buf[4];
    int n = read(fd, buf, sizeof(buf));
    close(fd);

    if (n < 2) return 0;

    if (n >= 4 && buf[0] == 0x7f && buf[1] == 'E' && buf[2] == 'L' && buf[3] == 'F')
        return 1;

    if (buf[0] == '#' && buf[1] == '!')
        return 1;

    return 0;
}

void scan(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (lstat(fullpath, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode)) {
            scan(fullpath);
        } else if (S_ISREG(st.st_mode)) {

            if (is_executable(st.st_mode)) {
                int suspicious = 0;

                if (!is_valid_executable(fullpath))
                    suspicious = 1;

                if (is_suspicious_permissions(st.st_mode))
                    suspicious = 1;

                if (suspicious) {
                    printf("Suspicious file: %s\n", fullpath);
                }
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *start = (argc > 1) ? argv[1] : ".";

    printf("Scanning: %s\n\n", start);
    scan(start);

    return 0;
}