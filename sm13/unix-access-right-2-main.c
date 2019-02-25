#include <stdio.h>
#include "unix-access-right-2.c"

int main() {
    unsigned gids[] = {
        10, 20, 30, 40, 50
    };
    int gid_count = 4;
    struct stat stb;
    struct Task task = { 0, gid_count, gids };
    int access;
    while (scanf(
                "%u%u%u%o%o",
                &(task.uid), &(stb.st_uid), &(stb.st_gid), &(stb.st_mode), &access
                ) == 5) {
        printf("%d\n", myaccess(&stb, &task, access));
    }
}
