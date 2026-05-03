#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;

    printf("Custom ls\n");

    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s  ", dir->d_name);
        }
        printf("\n");
        closedir(d);
    } else {
        perror("opendir");
        return 1;
    }

    printf("\n[INFO] This is not real ls.\n");

    return 0;
}