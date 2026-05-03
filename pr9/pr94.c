#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_command(const char *cmd) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        execlp(cmd, cmd, NULL);

        perror("execlp");
        exit(1);
    } else {
        wait(NULL);
    }
}

int main() {
    printf("=== whoami ===\n");
    run_command("whoami");

    printf("\n=== id ===\n");
    run_command("id");

    return 0;
}