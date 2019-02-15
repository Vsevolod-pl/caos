#include <sys/types.h>

struct FileContent {
    ssize_t size;
    char *data;
};

enum { BUFFER_SIZE = 4096 };

struct FileContent read_file(int fd) {
    char buf[BUFFER_SIZE];
    
}

