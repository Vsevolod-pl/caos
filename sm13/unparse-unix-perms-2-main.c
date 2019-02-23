#include "unparse-unix-perms-2.c"

enum { BUF_SIZE = 20 };

int main() {
    char buf[BUF_SIZE] = "abcdefghijklmnopqrs\0";
    int buf_size, mode;
    while (scanf("%d%o", &buf_size, &mode) == 2) {
        printf("%s\n", perms_to_str(buf, buf_size, mode));
        printf("%s\n", buf);
    }
    return 0;
}

