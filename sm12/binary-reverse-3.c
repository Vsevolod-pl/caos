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

enum { ERROR_MSG_LENGTH = 11 };

int handle_error(ssize_t fd0, ssize_t fd1, const char* errmsg, int errcode) {
    close(fd0);
    close(fd1);
    fprintf(stderr, "%*s", ERROR_MSG_LENGTH, errmsg);
    return errcode;
}

int is_sum_int64_overflow(int64_t first, int64_t second) {
    if (first > 0 && second > 0) {
        return first > MAX_INT64() - second;
    } else if (first < 0 && second < 0) {
        return first < MIN_INT64() - second;
    }
    return 0;
}

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
    struct Data left_data, right_data;  // No more!
    ssize_t left_fd = open(argv[1], O_RDWR);
    ssize_t right_fd = open(argv[1], O_RDWR);
    if (left_fd == -1) {
        return handle_error(left_fd, right_fd, "OPEN  LEFT ", 2);
    }
    if (right_fd == -1) {
        return handle_error(left_fd, right_fd, "OPEN  RIGHT", 2);
    }
    off_t left_pos = 0, right_pos = lseek(right_fd, 0, SEEK_END);
    ssize_t err_code;
    int64_t addend;
    while (left_pos < right_pos) {
        // Read left one.
        err_code = read(left_fd, &buf, sizeof(struct Data));
        if (err_code != sizeof(struct Data)) {
            return handle_error(left_fd, right_fd, "READ  LEFT ", 2);
        }
        // Move cursor back.
        left_pos = lseek(left_fd, -sizeof(struct Data), SEEK_CUR);
        if (left_pos == -1) {
            return handle_error(left_fd, right_fd, "LSEEK LEFT ", 2);
        }
        unmarshall(&left_data, &buf);
        addend = left_data->x;
        addend *= multiplier;
        if (is_sum_int64_overflow(left_data->y, addend)) {
            return handle_error(left_fd, right_fd, "OVERFLOW L ", 3);
        }
        left_data->y += addend;

        // Read the right one.
        err_code = read(right_fd, &buf, sizeof(struct Data));
        if (err_code != sizeof(struct Data)) {
            return handle_error(left_fd, right_fd, "READ  RIGHT", 2);
        }
        // Move cursor back.
        right_pos = lseek(right_fd, -sizeof(struct Data), SEEK_CUR);
        if (right_pos == -1) {
            return handle_error(left_fd, right_fd, "LSEEK RIGHT", 2);
        }
        unmarhsall(&right_data, &buf);
        addend = right_data->x;
        addend *= multiplier;
        // !!!TODO: Finish it :)
        // if (is_sum...)

    }
    if (left_pos == right_pos) {
        // Odd number of items. Do one change.
        
    }
    // else: entire file is reversed, all items are changed.
    
}

