#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void run_ls(const char *path) {
    printf("\n===== ls -l %s =====\n", path);
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ls -l %s", path);
    system(cmd);
}

void check_access(const char *file) {
    printf("\nAccess check: %s\n", file);

    printf("  read:    %s\n", access(file, R_OK) == 0 ? "YES" : "NO");
    printf("  write:   %s\n", access(file, W_OK) == 0 ? "YES" : "NO");
    printf("  execute: %s\n", access(file, X_OK) == 0 ? "YES" : "NO");
}

void scan_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < 5) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        check_access(fullpath);
        count++;
    }

    closedir(dir);
}

int main() {
    const char *home = getenv("HOME");

    printf("User: %s\n", getenv("USER"));

    run_ls(home);
    run_ls("/usr/bin");
    run_ls("/etc");

    printf("\n===== Access demonstration =====\n");

    printf("\n--- HOME sample ---");
    scan_directory(home);

    printf("\n--- /usr/bin sample ---");
    scan_directory("/usr/bin");

    printf("\n--- /etc sample ---");
    scan_directory("/etc");

    return 0;
}