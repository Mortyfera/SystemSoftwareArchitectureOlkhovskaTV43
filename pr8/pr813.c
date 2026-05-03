#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 32

int main() {
    int fd = open("test.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (ftruncate(fd, SIZE) == -1) {
        perror("ftruncate");
        return 1;
    }

    char *map = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    int pid = fork();

    if (pid == 0) {
        sleep(1);
        memset(map, 'M', SIZE);
        msync(map, SIZE, MS_SYNC);
        munmap(map, SIZE);
        close(fd);
        exit(0);
    } else {
        char buf[SIZE];
        memset(buf, 'W', SIZE);

        write(fd, buf, SIZE);

        wait(NULL);

        lseek(fd, 0, SEEK_SET);
        char result[SIZE + 1];
        read(fd, result, SIZE);
        result[SIZE] = '\0';

        printf("Final file content:\n%s\n", result);

        munmap(map, SIZE);
        close(fd);
    }

    return 0;
}