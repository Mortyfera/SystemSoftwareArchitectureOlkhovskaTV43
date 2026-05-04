#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define WORKERS 3

pid_t workers[WORKERS];
int tasks_assigned = 0;
int tasks_completed = 0;

void handle_done(int sig) {
    tasks_completed++;
    printf("[Parent] Task completed! Total: %d\n", tasks_completed);
}

void worker_process() {
    signal(SIGUSR1, SIG_IGN);

    while (1) {
        pause();

        printf("[Worker %d] Got task!\n", getpid());

        sleep(1 + rand() % 3);

        printf("[Worker %d] Done!\n", getpid());

        kill(getppid(), SIGUSR2);
    }
}

void handle_task(int sig) {
}

int main() {
    signal(SIGUSR2, handle_done);

    for (int i = 0; i < WORKERS; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            signal(SIGUSR1, handle_task);
            worker_process();
            exit(0);
        } else {
            workers[i] = pid;
        }
    }

    sleep(1);

    for (int i = 0; i < 5; i++) {
        int w = i % WORKERS;

        printf("[Parent] Assign task %d to worker %d\n", i + 1, workers[w]);
        kill(workers[w], SIGUSR1);

        tasks_assigned++;
        sleep(1);
    }

    while (tasks_completed < tasks_assigned) {
        pause();
    }

    printf("[Parent] All tasks done!\n");

    for (int i = 0; i < WORKERS; i++) {
        kill(workers[i], SIGKILL);
        wait(NULL);
    }

    return 0;
}