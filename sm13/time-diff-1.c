#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

enum { MAX_LINE_LENGTH = 1000 };

size_t my_getline(int in_fd, unsigned char *s) {
    fprintf(stderr, "Start getline()\n");
    ssize_t num_bytes = read(in_fd, s, MAX_LINE_LENGTH);
    fprintf(stderr, "num_bytes == %d\n", num_bytes);
    if (num_bytes <= 0) {
        return 0;
    }
    size_t i;
    for (i = 0; i != num_bytes; ++i) {
        if (s[i] == '\n') {
            s[i] = '\0';
            fprintf(stderr, "num_bytes, i == %d, %d\n", num_bytes, i);
            int pos = lseek(in_fd, i + 1 - num_bytes, SEEK_CUR);
            fprintf(stderr, "pos == %d\n", pos);
            fprintf(stderr, "num_bytes == %d\n", num_bytes);
            return i;
        }
    }
    s[i] = '\0';
    fprintf(stderr, "num_bytes == %d\n", num_bytes);
    return num_bytes;
}

enum { YEAR_SIZE = 4, MONTH_SIZE = 2, DAY_SIZE = 2 };
enum { HOUR_SIZE = 2, MINUTE_SIZE = 2, SECOND_SIZE = 2 };

enum { YEAR_SHIFT = 1900, MONTH_SHIFT = 1, DAY_SHIFT = 0 };
enum { HOUR_SHIFT = 0, MINUTE_SHIFT = 0, SECOND_SHIFT = 0 };

int to_int(const unsigned char *in, int length) {
    int result = 0;
    for (size_t i = 0; i != length; ++i) {
        int digit = *(in + i) - (unsigned char)'0';
        result = result * 10 + digit;
    }
    return result;
}

struct tm parse_tm(const unsigned char *s, size_t size) {
    struct tm time;
    size_t i;
    for (i = 0; i != size && s[i] == ' '; ++i) {}
    time.tm_year = to_int(s + i, YEAR_SIZE) - YEAR_SHIFT;
    i += YEAR_SIZE + 1;
    time.tm_mon = to_int(s + i, MONTH_SIZE) - MONTH_SHIFT;
    i += MONTH_SIZE + 1;
    time.tm_mday = to_int(s + i, DAY_SIZE) - DAY_SHIFT;
    i += DAY_SIZE + 1;
    for (; i != size && s[i] == ' '; ++i) {}
    time.tm_hour = to_int(s + i, HOUR_SIZE) - HOUR_SHIFT;
    i += HOUR_SIZE + 1;
    time.tm_min = to_int(s + i, MINUTE_SIZE) - MINUTE_SHIFT;
    i += MINUTE_SIZE + 1;
    time.tm_sec = to_int(s + i, SECOND_SIZE) - SECOND_SHIFT;
    time.tm_isdst = -1;
    // DEBUG
    fprintf(stderr, "%02d.%02d.%04d, %02d:%02d:%02d\n",
            time.tm_mday, time.tm_mon, time.tm_year, time.tm_hour, time.tm_min, time.tm_sec);
    // DEBUG
    return time;
}

int main(int argc, char **argv) {
    unsigned char buf[MAX_LINE_LENGTH + 1];
    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd == -1) {
        return 0;
    }
    size_t line_length = my_getline(in_fd, buf);
    struct tm tm_time = parse_tm(buf, line_length);
    time_t prev = mktime(&tm_time);
    while ((line_length = my_getline(in_fd, buf)) != 0) {
        fprintf(stderr, "Stop getline()\n");
        struct tm tm_time = parse_tm(buf, line_length);
        time_t current = mktime(&tm_time);
        printf("%d\n", (int32_t)current - (int32_t)prev);
        prev = current;
    }
    fprintf(stderr, "Stop getline()\n");
    close(in_fd);
    return 0;
}

