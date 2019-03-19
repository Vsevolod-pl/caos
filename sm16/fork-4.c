#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { INPUT_SIZE = 8, NUM_SONS = 3 };

int32_t read_number() {
    char buf[INPUT_SIZE];
    if (read(0, &buf, INPUT_SIZE) != INPUT_SIZE) {
        exit(1);
    }
    int64_t value = strtol(buf, NULL, 10);
    if (value == (int32_t)value) {
        return value;
    }
    exit(1);
}

int main() {
    for (size_t i = 0; i != NUM_SONS; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            return 1;
        }
        if (!pid) {
            int32_t item = read_number();
            printf("%d %d\n", i + 1, item * item);
            return 0;
        }
    }
    for (size_t i = 0; i != NUM_SONS; ++i) {
        wait(NULL);
    }
    return 0;
}
