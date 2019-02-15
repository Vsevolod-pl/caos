#include <sys/types.h>
#include <unistd.h>

enum { BUFFER_SIZE = 4096 };

void copy_file(int in_fd, int out_fd) {
    unsigned char buf[BUFFER_SIZE];
    ssize_t num_read;
    while ((num_read = read(in_fd, buf, BUFFER_SIZE)) > 0) {
        ssize_t num_total_write = 0, num_write;
        while (num_total_write != num_read) {
            if ((num_write = write(out_fd, buf + num_total_write, num_read - num_total_write)) != -1) {
                num_total_write += num_write;
            } else {
                // Stop writing.
                return;
            }
        }
    }
    return;
}

