#include <stdio.h>
#include <stdlib.h>

enum { NUM_FLAGS = 9 };

enum {
    SUID_POS = 11, SGID_POS = 10, STICKY_POS = 9,
    UR_POS = 8, UW_POS = 7, UX_POS = 6,
    GR_POS = 5, GW_POS = 4, GX_POS = 3,
    OR_POS = 2, OW_POS = 1, OX_POS = 0,
};

const char FLAGS[3] = "rwx";

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        return buf;
    }
    if (size > NUM_FLAGS + 1) {
        size = NUM_FLAGS + 1;
    }
    for (int i = 0; i + 1 != size; ++i) {
        buf[i] = '-';
    }
    buf[size - 1] = '\0';
    for (size_t i = 0; i + 1 != size; ++i) {
        if (perms & (1 << (NUM_FLAGS - i - 1))) {
            buf[i] = FLAGS[i % 3];
        }
    }
    if ((perms & (1 << SUID_POS)) && ((perms & (1 << GX_POS)) || (perms & (1 << OX_POS)))) {
        if (NUM_FLAGS - UX_POS < size) {
            buf[NUM_FLAGS - UX_POS - 1] = 's';
        }
    }
    if ((perms & (1 << SGID_POS)) && (perms & (1 << OX_POS))) {
        if (NUM_FLAGS - GX_POS < size) {
            buf[NUM_FLAGS - GX_POS - 1] = 's';
        }
    }
    if ((perms & (1 << STICKY_POS)) && (perms & (1 << OX_POS)) && (perms & (1 << OW_POS))) {
        if (NUM_FLAGS - OX_POS < size) {
            buf[NUM_FLAGS - OX_POS - 1] = 't';
        }
    }
    return buf;
}

