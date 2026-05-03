#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SRC "/tmp/root_created.txt"

int copy_file(const char *src, const char *dst) {
    int in = open(src, O_RDONLY);
    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (in < 0 || out < 0) {
        perror("open");
        return -1;
    }

    char buf[1024];
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        if (write(out, buf, n) != n) {
            perror("write");
            return -1;
        }
    }

    close(in);
    close(out);
    return 0;
}

int main() {
    uid_t ruid = getuid();
    uid_t euid = geteuid();

    struct passwd *pw = getpwuid(ruid);
    if (!pw) {
        perror("getpwuid");
        return 1;
    }

    char dst[512];
    snprintf(dst, sizeof(dst), "%s/copied_by_root.txt", pw->pw_dir);

    printf("Real UID = %d, Effective UID = %d\n", ruid, euid);

    int fd = open(SRC, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    write(fd, "Secret data\n", 12);
    close(fd);

    printf("File created by root: %s\n", SRC);

    if (copy_file(SRC, dst) == 0) {
        printf("Copied to: %s\n", dst);
    }

    seteuid(ruid);
    printf("\nSwitched to normal user (EUID=%d)\n", geteuid());

    fd = open(dst, O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("Modify attempt");
    } else {
        write(fd, "User modification\n", 18);
        close(fd);
        printf("File modified successfully\n");
    }

    if (unlink(dst) == 0) {
        printf("File deleted successfully\n");
    } else {
        perror("Delete attempt");
    }

    return 0;
}