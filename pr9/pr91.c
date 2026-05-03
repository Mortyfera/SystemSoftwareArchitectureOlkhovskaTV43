#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#define LINE_SIZE 1024

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    uid_t my_uid = getuid();
    struct passwd *pw = getpwuid(my_uid);
    char *my_name = pw ? pw->pw_name : NULL;

    int found = 0;
    char line[LINE_SIZE];

    while (fgets(line, sizeof(line), fp)) {
        char *username = strtok(line, ":");
        strtok(NULL, ":");
        char *uid_str = strtok(NULL, ":");

        if (!username || !uid_str)
            continue;

        int uid = atoi(uid_str);

        if (uid > 1000 && my_name && strcmp(username, my_name) != 0) {
            printf("Other regular user: %s (UID=%d)\n", username, uid);
            found = 1;
        }
    }

    pclose(fp);

    if (!found) {
        printf("No other regular users found.\n");
    }

    return 0;
}