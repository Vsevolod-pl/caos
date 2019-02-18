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

enum { NUM = 1 };

int main(int argc, char **argv) {
    int32_t keys[NUM] = {
        666
    };
    int32_t left_ids[NUM] = {
        0
    };
    int32_t right_ids[NUM] = {
        0
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
