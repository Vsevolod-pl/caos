#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

ssize_t traverse(int fd, int id) {
    lseek(fd, id * sizeof(struct Node), SEEK_SET);
    struct Node buf;
    ssize_t errcode = read(fd, &buf, sizeof(struct Node));
    if (errcode != sizeof(struct Node)) {
        return 1;
    }
    if (buf.right_idx) {
        errcode = traverse(fd, buf.right_idx);
        if (errcode) {
            return 1;
        }
    }
    printf("%d ", buf.key);
    if (buf.left_idx) {
        errcode = traverse(fd, buf.left_idx);
        if (errcode) {
            return 1;
        }
    }
    if (id == 0) {
        printf("\n");
    }
    return 0;
}

int is_file_empty(int fd) {
    off_t pos = lseek(fd, 0, SEEK_END);
    if (pos == 0) {
        return 1;
    }
    pos = lseek(fd, 0, SEEK_SET);
    return 0;
}

// argv[1] == input file
int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    if (is_file_empty(fd)) {
        close(fd);
        return 1;
    }
    ssize_t errcode = traverse(fd, 0);
    close(fd);
    return errcode;
}

