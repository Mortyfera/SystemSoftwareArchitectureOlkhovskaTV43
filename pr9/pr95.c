#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

static int can_read(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return 0;
    close(fd);
    return 1;
}

static int can_write(const char *path) {
    int fd = open(path, O_WRONLY | O_APPEND);
    if (fd < 0) return 0;
    close(fd);
    return 1;
}

static void print_result(const char *label, const char *path) {
    printf("%-30s | read=%s write=%s\n",
           label,
           can_read(path) ? "YES" : "NO",
           can_write(path) ? "YES" : "NO");
}

int main() {
    uid_t ruid = getuid();
    uid_t euid = geteuid();
    gid_t rgid = getgid();

    struct passwd *pw = getpwuid(ruid);
    if (!pw) { perror("getpwuid"); return 1; }

    char path[512];
    snprintf(path, sizeof(path), "%s/tmp_perm_test.txt", pw->pw_dir);

    printf("Start: ruid=%d euid=%d (should be root euid via SUID)\n", ruid, euid);

    if (seteuid(ruid) != 0) { perror("seteuid user"); return 1; }

    int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd < 0) { perror("open create"); return 1; }
    write(fd, "initial\n", 8);
    close(fd);

    printf("File created as user: %s (mode 0600)\n", path);

    if (seteuid(0) != 0) { perror("seteuid root"); return 1; }

    if (chown(path, 0, 0) != 0) {
        perror("chown");
    }

    mode_t modes[] = {
        0600,
        0644,
        0666,
        0400,
        0000
    };
    const char *labels[] = {
        "root owner, 0600",
        "root owner, 0644",
        "root owner, 0666",
        "root owner, 0400",
        "root owner, 0000"
    };

    printf("\nSwitch back to user and test access:\n");

    for (int i = 0; i < 5; i++) {
        if (chmod(path, modes[i]) != 0) {
            perror("chmod");
        }

        if (seteuid(ruid) != 0) { perror("seteuid user (test)"); return 1; }

        print_result(labels[i], path);

        if (seteuid(0) != 0) { perror("seteuid root (loop)"); return 1; }
    }

    unlink(path);
    printf("\nCleanup done.\n");

    return 0;
}