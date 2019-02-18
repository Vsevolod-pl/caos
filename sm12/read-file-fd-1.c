#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

enum { BUFFER_SIZE = 4096 };

struct FileContent
{
    ssize_t size;
    char *data;
};

struct FileContent read_file(int fd) {
    char buf[BUFFER_SIZE];
    struct FileContent file;
    ssize_t num_read;
    ssize_t current_size = 0;
    int buffer_filled = 0;
    while ((num_read = read(fd, buf + buffer_filled, BUFFER_SIZE - buffer_filled)) > 0) {
        if (num_read == BUFFER_SIZE - buffer_filled) {
            // Buffer is filled! Do the flush.
            char *new_data = realloc(file.data, current_size + BUFFER_SIZE);
            if (new_data) {
                file.data = new_data;
                memcpy(file.data + current_size, buf, BUFFER_SIZE);
                current_size += BUFFER_SIZE;
            } else {
                file.size = -1;
                if (file.data) {
                    free(file.data);
                }
                file.data = NULL;
                return file;
            }
        } else {
            buffer_filled += num_read;
        }
    }
    if (num_read == -1) {
        file.size = -1;
        if (file.data) {
            free(file.data);
        }
        file.data = NULL;
        return file;
    }
    // Do the flush and add \0
    char *new_data = realloc(file.data, current_size + buffer_filled + 1);
    if (new_data) {
        file.data = new_data;
        memcpy(file.data + current_size, buf, buffer_filled);
        current_size += buffer_filled;
        // Do not increment file.size or current_size!!! \0 don't count.
        *(file.data + current_size) = 0;
        file.size = current_size;
    } else {
        file.size = -1;
        if (file.data) {
            free(file.data);
        }
        file.data = NULL;
    }
    return file;
}

