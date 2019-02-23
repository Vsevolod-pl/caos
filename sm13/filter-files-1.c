#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct stat buf;
    uint64_t total_size = 0ULL;
    for (size_t i = 1; i != argc; ++i) {
        lstat(argv[i], &buf);
        if (access(argv[i], F_OK) != -1) {
            // File exists, stat's return -1.
            if (S_ISREG(buf.st_mode) && !S_ISLNK(buf.st_mode)) {
                // File is regular, not a symlink.
                if (buf.st_nlink == 1) {
                    // File has only one name in file system.
                    total_size += buf.st_size;
                    // total_size += get_file_size(in_fd);
                }
            }
        }
    }
    printf("%llu\n", total_size);
    return 0;
}

