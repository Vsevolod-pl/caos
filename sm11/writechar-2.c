#include <asm/unistd_32.h>

struct FileWriteState
{
    int fd;
    unsigned char *buf;
    int bufsize;
};

struct FileWriteState *stout;

enum { BUFFER_SIZE = 4 * 1024 };

void __attribute__((fastcall)) writechar(int c, struct FileWriteState *out) {

}

void flush(struct FileWriteState *out) {

}

