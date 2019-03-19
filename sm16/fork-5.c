#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int num_childs;
    if (scanf("%d", &num_childs) != 1) {
        return 1;
    }
    for (size_t i = 0; i != num_childs; ++i) {
        if (i + 1 == num_childs) {
            printf("%d\n", i + 1);
        } else {
            printf("%d ", i + 1);
        }
        // fflush(stdout);
        pid_t pid = fork();
        if (pid < 0) {
            return 1;
        }
        if (!pid) {
            // child
            continue;
        } else {
            wait(NULL);
            exit(0);
        }
    }
    exit(0);
}

