#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void neg_(long long *item) {
    unsigned long long u_item = *item;
    if (u_item == (1ULL << (8 * sizeof(long long) - 1))) {
        return;
    }
    *item *= -1;
    return;
}

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDWR);
    size_t file_size = lseek(fd, 0, SEEK_END);
    size_t num_items = file_size / sizeof(long long);
    if (num_items == 0) {
        close(fd);
        return 0;
    }
    // Return the cursor to begin.
    lseek(fd, 0, SEEK_SET);
    long long min_item;
    int errcode = read(fd, &min_item, sizeof(long long));
    if (errcode != sizeof(long long)) {
        close(fd);
        return 1;
    }
    size_t min_pos = 0;
    long long buf;
    for (size_t i = 1; i < num_items; ++i) {
        errcode = read(fd, &buf, sizeof(long long));
        if (errcode != sizeof(long long)) {
            close(fd);
            return 1;
        }
        if (min_item > buf) {
            min_item = buf;
            min_pos = i;
        }
    }
    lseek(fd, sizeof(long long) * min_pos, SEEK_SET);
    neg_(&min_item);
    errcode = write(fd, &min_item, sizeof(long long));
    if (errcode != sizeof(long long)) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

