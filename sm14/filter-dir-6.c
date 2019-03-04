#include <ctype.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough argv\n");
        return 1;
    }
    DIR* dir = opendir(argv[1]);
    if (!dir) {
        fprintf(stderr, "Error while opendir()\n");
        return 1;
    }
    struct dirent *entry;
    struct stat buf;
    uint64_t total_size = 0ULL;
    char pathname[PATH_MAX + 1];
    while ((entry = readdir(dir))) {
        snprintf(pathname, sizeof(pathname), "%s/%s", argv[1], entry->d_name);
        if (stat(pathname, &buf) >= 0) {
            if (S_ISREG(buf.st_mode)) {
                if (getuid() == buf.st_uid) {
                    if (isupper(entry->d_name[0])) {
                        total_size += buf.st_size;
                    }
                }
            }
        }
    }
    printf("%llu\n", total_size);
    return 0;
}

