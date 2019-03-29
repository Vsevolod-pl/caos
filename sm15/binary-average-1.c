#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "not enough argv\n");
        return 1;
    }

    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd < 0) {
        fprintf(stderr, "error while open()\n");
        return 0;
    }

    struct stat in_stb;
    int err = fstat(in_fd, &in_stb);
    if (err < 0) {
        fprintf(stderr, "Error while fstat()\n");
        close(in_fd);
        return 1;
    }

    // Check if file is empty.
    if (!in_stb.st_size) {
        printf("0\n");
        close(in_fd);
        return 0;
    }

    double *data = mmap(NULL, in_stb.st_size, PROT_READ, MAP_PRIVATE, in_fd, 0);
    if (data == MAP_FAILED) {
        close(in_fd);
        return 0;
    }
    close(in_fd);

    double sum = 0.0;
    size_t data_length = in_stb.st_size / sizeof(double);
    for (size_t i = 0; i != data_length; ++i) {
        sum += data[i];
    }
    fprintf(stdout, "%a\n", sum / data_length);

    munmap(data, in_stb.st_size);
    return 0;
}

