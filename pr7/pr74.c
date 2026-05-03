#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define PAGE_LINES 20
#define MAX_LINE 1024


int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char line[MAX_LINE];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        line_count++;

        if (line_count == PAGE_LINES) {
            printf("\n--More-- (Press any key, q to quit)\n");

            int c = getch();
            if (c == 'q' || c == 'Q') {
                fclose(file);
                exit(0);
            }

            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        process_file(argv[i]);
    }

    return 0;
}