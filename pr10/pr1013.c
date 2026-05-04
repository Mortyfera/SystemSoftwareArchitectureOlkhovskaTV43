#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = 0;

        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}