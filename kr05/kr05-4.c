#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#include <stdio.h>

enum { NUM_BITS = 8 };

int main(int argc, char **argv) {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    unsigned x;
    unsigned char buf[sizeof(unsigned)];
    while (scanf("%u", &x) == 1) {
        for (int i = 0; i != sizeof(unsigned); ++i) {
            buf[sizeof(unsigned) - i - 1] = (x & ((1 << NUM_BITS) - 1));
            x >>= NUM_BITS;
        }
        int errcode = write(fd, buf, sizeof(unsigned));
        if (errcode != sizeof(unsigned)) {
            close(fd);
            return 1;
        };
    }
    close(fd);
    return 0;
}

