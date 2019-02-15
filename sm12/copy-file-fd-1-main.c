#include <fcntl.h>
#include "copy-file-fd-1.c"

int main(int argc, char *argv[]) {
    int f1 = open(argv[1], O_RDONLY);
    int f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0400);
    copy_file(f1, f2);
    close(f1);
    close(f2);
    return 0;
}

