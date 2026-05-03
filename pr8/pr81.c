#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);
    int flags = fcntl(fd[1], F_GETFL, 0);
    fcntl(fd[1], F_SETFL, flags | O_NONBLOCK);

    char buffer[65536];
    memset(buffer, 'A', sizeof(buffer));

    int total_written = 0;

    while (1) {
        int count = write(fd[1], buffer, sizeof(buffer));

        if (count == -1) {
            perror("write");
            break;
        }

        printf("Requested: %ld, Written: %d\n",
               sizeof(buffer), count);

        if (count < sizeof(buffer)) {
            printf("\nPartial write detected!\n");
            break;
        }

        total_written += count;
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}