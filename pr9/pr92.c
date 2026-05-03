#include <unistd.h>
#include <stdio.h>

int main() {
    execlp("sudo", "sudo", "cat", "/etc/shadow", NULL);

    perror("execlp");
    return 1;
}