#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd >= 0) {
        unsigned short x;
        unsigned char out[2];
        while (scanf("%hu", &x) == 1) {
            out[0] = x >> CHAR_BIT;
            out[1] = x;
            ssize_t code = write(fd, &out, 2);
            ++code;
        }
        close(fd);
    }
    return 0;
}

