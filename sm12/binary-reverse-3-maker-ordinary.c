#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#pragma pack(push, 1)
struct Data
{
    int16_t x;
    int64_t y;
};
#pragma pack(pop)

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

// argv[1] == input file
// argv[2] == number of structs
int main(int argc, char **argv) {
    if (argc < 3) {
        abort();
    }
    int16_t xs[] = {
        10,
        11,
        12,
        13,
        14,
        15,
        16
    };
    int64_t ys[] = {
        -10,
        -11,
        -12,
        -13,
        -14,
        -15,
        -16
    };
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    int32_t num_data;
    if (!is_int32(argv[2], &num_data)) {
        abort();
    }
    for (int i = 0; i != num_data; ++i) {
        struct Data data = {
            xs[i], ys[i]
        };
        ssize_t errcode = write(fd, (char *)&data, sizeof(struct Data));
        if (errcode == -1) {
            abort();
        }
    };
    close(fd);
    return 0;
}
