#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Data
{
    int16_t x;
    int64_t y;
};

void marshall(unsigned char *out, const struct Data *in) {
}

void unmarshall(struct Data *out, const unsigned char *in) {

}

int is_int32(char *arg, int32_t *dst) {
    char *eptr;
    errno = 0;
    int64_t value = strtol(arg, &eptr, 10);
    if (!*arg || *eptr || errno) {
        return 0;
    }
    if (value == (int32_t)value) {
        *dst = value;
        return 1;
    } else {
        return 0;
    }
}

int64_t MAX_INT64() {
    return ~0ULL >> 1;
}

int64_t MIN_INT64() {
    return ~MAX_INT64();
}

int is_sum_int64_overflow(int64_t first, int64_t second) {
    if (first > 0 && second > 0) {
        return first > MAX_INT64() - second;
    } else if (first < 0 && second < 0) {
        return first < MIN_INT64() - second;
    }
    return 0;
}

// uint64_t get_file_size(int fd) {
// }

// argv[1] == binary file name
// argv[2] == int32_t (multiplier)
int main(int argc, char** argv) {
    unsigned char buf[sizeof(struct Data)];
    int32_t multiplier;
    if (argc < 3) {
        abort();
    }
    if (!is_int32(argv[2], &multiplier)) {
        abort();
    }
    struct Data left, right;  // No more!
    int left_fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Error while opening file the first time");
        return 2;
    }
    int right_fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Error while opening file the second time");
        return 2;
    }
    fprintf(stderr, "current file pos == %lu\n", lseek(fd, -1, SEEK_END));
}

