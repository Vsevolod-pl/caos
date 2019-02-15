#include <sys/types.h>
#include <unistd.h>

enum { BUFFER_SIZE = 4096 };

void copy_file(int in_fd, int out_fd) {
    char buf[BUFFER_SIZE];
    ssize_t num_total_read;
    while ((num_total_read = read(in_fd, buf, BUFFER_SIZE)) > 0) {
        ssize_t num_total_write = 0, num_write;
        while (num_total_write != num_total_read) {
            if ((num_write = write(out_fd, buf + num_total_write, num_total_read - num_total_write)) != -1) {
                num_total_write += num_write;
            } else {
                // Stop writing.
                return;
            }
        }
    }
    return;
}

