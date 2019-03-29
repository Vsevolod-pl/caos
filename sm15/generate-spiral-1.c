#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

void fill_spirally(int32_t *data, int height, int width, int32_t first) {
    int column_start = 0;
    int row_start = 0;
    int column_stop = width;
    int row_stop = height;
    while (column_start < column_stop && row_start < row_stop) {
        for (int column = column_start; column != column_stop; ++column) {
            data[row_start * width + column] = first++;
        }
        ++row_start;

        if (row_start >= row_stop) {
            break;
        }
        for (int row = row_start; row != row_stop; ++row) {
            data[row * width + (column_stop - 1)] = first++;
        }
        --column_stop;

        if (column_start >= column_stop) {
            break;
        }
        for (int column = column_stop - 1; column != column_start - 1; --column) {
            data[(row_stop - 1) * width + column] = first++;
        }
        --row_stop;

        if (row_start >= row_stop) {
            break;
        }
        for (int row = row_stop - 1; row != row_start - 1; --row) {
            data[row * width + column_start] = first++;
        }
        ++column_start;
    }
}

int main(int argc, char **argv) {
    // Parse arguments.
    if (argc < 4) {
        fprintf(stderr, "not enough argv\n");
        return 1;
    }
    int32_t height, width;
    if (sscanf(argv[2], "%d", &height) != 1) {
        fprintf(stderr, "cannot parse number of rows\n");
        return 1;
    }
    if (sscanf(argv[3], "%d", &width) != 1) {
        fprintf(stderr, "cannot parse number of columns\n");
        return 1;
    }

    int out_fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0) {
        fprintf(stderr, "Error while open()\n");
        return 1;
    }
    
    int64_t file_size = height * width * sizeof(int32_t);

    if (ftruncate(out_fd, file_size)) {
        fprintf(stderr, "Error while ftruncate()\n");
        close(out_fd);
        return 1;
    }
    int32_t *data = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, out_fd, 0);
    if (data == MAP_FAILED) {
        fprintf(stderr, "Error while mmap()\n");
        close(out_fd);
        return 1;
    }
    close(out_fd);

    fill_spirally(data, height, width, 1);

    munmap(data, file_size);
    return 0;
}

