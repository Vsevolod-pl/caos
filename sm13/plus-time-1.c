#include <stdint.h>
#include <stdio.h>
#include <time.h>

enum { SECONDS_PER_DAY = 60 * 60 * 24 };

int main() {
    time_t current_time = time(NULL);
    int32_t days_after;
    while (scanf("%d", &days_after) == 1) {
        int64_t seconds_after = (int64_t)days_after * SECONDS_PER_DAY;
        if ((int32_t)seconds_after == seconds_after && seconds_after >= INT32_MIN && seconds_after <= INT32_MAX) {
            seconds_after += current_time;
            if ((time_t)seconds_after == seconds_after && seconds_after >= INT32_MIN && seconds_after <= INT32_MAX) {
                time_t augmented_time = seconds_after;
                struct tm *p = localtime(&augmented_time);
                printf(
                    "%04d-%02d-%02d\n",
                    p->tm_year + 1900,
                    p->tm_mon + 1,
                    p->tm_mday
                );
                continue;
            }
        }
        printf("OVERFLOW\n");
    }
}

