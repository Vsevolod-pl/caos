#include <asm/unistd_32.h>

enum { BUFFER_SIZE = 1 };

void _start() {
    char ch;
    int code;
    while (42) {
        asm(
            "int $0x80"
            : "=a" (code)
            : "a" (__NR_read), "b" (0), "c" (&ch), "d" (BUFFER_SIZE)

        );
        if (code != BUFFER_SIZE) {
            break;
        }
        if ('a' <= ch && ch <= 'z') {
            ch += 'A' - 'a';
        }
        asm(
            "int $0x80"
            : "=a" (code)
            : "a" (__NR_write), "b" (1), "c" (&ch), "d" (BUFFER_SIZE)
        );
    }
    asm(
        "int     $0x80"
        : 
        : "a" (__NR_exit), "b" (0)
    );
}

