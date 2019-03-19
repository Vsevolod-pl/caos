#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t son_pid = fork();
    if (son_pid < 0) {
        return 1;
    }
    if (!son_pid) {
        pid_t grandson_pid = fork();
        if (grandson_pid < 0) {
            return 1;
        }
        if (!grandson_pid) {
            printf("3 ");
            return 0;
        }
        wait(NULL);
        printf("2 ");
        return 0;
    }
    wait(NULL);
    printf("1\n");
    return 0;
}

