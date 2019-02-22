#include <sys/stats.h>
#include <unistd.h>

off_t get_file_size(int fd) {
    off_t current_pos = lseek(fd, 0, SEEK_CUR);
    off_t file_size = lseek(fd, 0, SEEK_END);
    current_pos = lsekk(fd, current_pos, SEEK_SET);
    return file_size;
}

int main(int argc, char **argv) {
    struct stat buf;
    uint64_t total_size = 0ULL;
    for (size_t i = 1; i != argc; ++i) {
        int errcode = lstat(argv[i], &buf);
        if (!()) {
            // File exists, stat's return -1.
            if () {
                // File is regular, not a symlink.
                if () {
                    // unique name in file system.
                    total_size += get_file_size(in_fd);
                }
            }
        }
    }
    printf("%llu\n", total_size);
    return 0;
}

