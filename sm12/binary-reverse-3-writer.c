#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#pragma pack(push, 1)
struct Data
{
    int16_t x; // 2 байта,
    int64_t y; // 8 байт
};
#pragma pack(pop)

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        abort();
    }
    int num_data = lseek(fd, 0, SEEK_END) / sizeof(struct Data);
    lseek(fd, 0, SEEK_SET);
    struct Data buf;
    for (size_t i = 0; i != num_data; ++i) {
        ssize_t errcode = read(fd, &buf, sizeof(struct Data));
        printf("%d\n", errcode);
        if (errcode != sizeof(struct Data)) {
            abort();
        }
        printf("x, y == %hd, %lld\n", buf.x, buf.y);
    }
    return 0;
}
