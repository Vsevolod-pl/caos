#include <fcntl.h>
#include <unistd.h>

enum {
    MAX_LINE_LENGTH = 1000;
};

size_t my_getline(int in_fd, unsigned char *s) {
    ssize_t num_bytes = read(in_fd, s, MAX_LINE_LENGTH);
    if (num_bytes <= 0) {
        return 0;
    }
    size_t i;
    for (i = 0; i != num_bytes; ++i) {
        if (s[i] == '\n') {
            s[i] = '\0';
            return i;
        }
    }
    s[i] = '\0';
    return num_bytes;
}

enum { YEAR_SIZE = 4, MONTH_SIZE = 2, DAY_SIZE = 2 };
enum { HOUR_SIZE = 2, MINUTE_SIZE = 2, SECOND_SIZE = 2 };

enum { YEAR_SHIFT = 1900, MONTH_SHIFT = 1, DAY_SHIFT = 0 };
enum { HOUR_SHIFT = 0, MINUTE_SHIFT = 1, SECOND_SHIFT = 0 };

struct tm parse_tm(const unsigned char *s, size_t size) {
    struct tm time;
    size_t i;
    for (i = 0; i != size && s[i] == ' '; ++i) {}
    time.tm_year = to_int(s[i], YEAR_SIZE) - YEAR_SHIFT;
    i += YEAR_SIZE + 1;
    time.tm_mon = to_int(s[i], MONTH_SIZE) - MONTH_SHIFT;
    i += MONTH_SIZE + 1;
    time.tm_mday = to_int(s[i], DAY_SIZE) - DAY_SHIFT;
    i += DAY_SIZE + 1;
    for (; i != size && s[i] == ' '; ++i) {}
    time.tm_hour = to_int(s[i], HOUR_SIZE) - HOUR_SHIFT;
    i += HOUR_SIZE + 1;
    time.tm_min = to_int(s[i], MINUTE_SIZE) - MINUTE_SHIFT;
    i += MINUTE_SIZE + 1;
    time.tm_sec = to_int(s[i], SECOND_SIZE) - SECOND_SHIFT;
    // DEBUG
    fprintf(stderr, "%02d.%02d.%04d, %02d:%02d:%02d\n",
            time.tm_mday, time.tm_mon, time.tm_year, time.tm_hour, time.tm_min, time.tm_sec);
    // DEBUG
    return time;
}

int main(int argc, char **argv) {
    unsigned char buf[MAX_LINE_LENGTH + 1];
    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd != -1) {
        return 0;
    }
    my_getline(in_fd, &buf);
    time_t prev = tm_to_time_t(parse_tm(buf)), current;
    size_t line_length;
    while ((line_length = my_getline(in_fd, buf)) != 0) {
        current = tm_to_time_t(parse_tm(buf, line_length));
        printf(current - prev);
        prev = current;
    }
    close(in_fd);
    return 0;
}

