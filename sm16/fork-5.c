#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int num_childs;
    if (scanf("%d", &num_childs) != 1) {
        return 1;
    }
    // printf("1");
    for (size_t i = 1; i != num_childs; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            return 1;
        }
        if (!pid) {
            fprintf(stderr, "%d is son of %d\n", getpid(), getppid());
            // printf(" %d", i);
        } else {
            wait(NULL);
        }
    }
    printf("\n");
    return 0;
}

