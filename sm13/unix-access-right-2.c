#include <stdlib.h>
#include <sys/stat.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

enum { GRANTED = 1, DENIED = 0 };
enum { THREE_BITS_MASK = 7U };

static int has_access(unsigned mode, unsigned shift, unsigned request) {
    mode = (mode >> shift) & THREE_BITS_MASK;
    request &= THREE_BITS_MASK;
    if ((mode & request) == request) {
        return GRANTED;
    } else {
        return DENIED;
    }
}

static int has_group_rights(const struct stat *stb, const struct Task *task) {
    for (size_t i = 0; i != task->gid_count; ++i) {
        if (stb->st_gid == task->gids[i]) {
            return 1;
        }
    }
    return 0;
}

enum { ROOT_ID = 0 };
enum { USER_SHIFT = 6, GROUP_SHIFT = 3, OTHERS_SHIFT = 0 };

int myaccess(const struct stat *stb, const struct Task *task, int access) {
    if (task->uid == ROOT_ID) {
        return GRANTED;
    }
    if (task->uid == stb->st_uid) {
        // It has user rights.
        return has_access(stb->st_mode, USER_SHIFT, access);
    }
    if (has_group_rights(stb, task)) {
        return has_access(stb->st_mode, GROUP_SHIFT, access);
    }
    // It has others rights.
    return has_access(stb->st_mode, OTHERS_SHIFT, access);
}

