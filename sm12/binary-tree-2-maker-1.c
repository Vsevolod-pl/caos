#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

enum { NUM = 23 };

int main(int argc, char **argv) {
    int32_t keys[NUM] = {
        512,
        256, 1024,
        60, 300, 900, 2048,
        30, 90, 275, 400, 800, 1000, 2000, 4096,
        10, 40, 80, 120, 700, 3000, 5000, 6000
    };
    int32_t left_ids[NUM] = {
        1,
        3, 5,
        7, 9, 11, 13,
        15, 17, 0, 0, 19, 0, 0, 20,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    int32_t right_ids[NUM] = {
        2,
        4, 6,
        8, 10, 12, 14,
        16, 18, 0, 0, 0, 0, 0, 21,
        0, 0, 0, 0, 0, 0, 22, 0
    };
    struct Node buf;
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    for (int i = 0; i != NUM; ++i) {
        buf.key = keys[i] * 1001;
        buf.left_idx = left_ids[i];
        buf.right_idx = right_ids[i];
        ssize_t errcode = write(fd, &buf, sizeof(struct Node));
        if (errcode == -1) {
            abort();
        }
    }
    close(fd);
}
