#include <stdio.h>
#include "read-file-fd-1.c"

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    struct FileContent file = read_file(fd);
    if (file.data) {
        printf("%s\n", file.data);
        fprintf(stderr, "file.size == %zd\n", file.size);
    } else {
        fprintf(stderr, "file.data == NULL\n");
        fprintf(stderr, "file.size == %zd\n", file.size);
    }
    free(file.data);
    close(fd);
}

