#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode) {
    char perms[11];

    perms[0] = S_ISDIR(mode) ? 'd' :
               S_ISLNK(mode) ? 'l' : '-';

    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';

    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';

    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';

    perms[10] = '\0';

    printf("%s ", perms);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        print_permissions(fileStat.st_mode);

        printf("%ld ", fileStat.st_nlink);

        struct passwd *pw = getpwuid(fileStat.st_uid);
        printf("%s ", pw ? pw->pw_name : "unknown");

        struct group *gr = getgrgid(fileStat.st_gid);
        printf("%s ", gr ? gr->gr_name : "unknown");

        printf("%5ld ", fileStat.st_size);

        char timebuf[80];
        struct tm *timeinfo = localtime(&fileStat.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", timeinfo);
        printf("%s ", timebuf);

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}