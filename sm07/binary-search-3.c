#include <stdlib.h>

struct BSearchResult
{
    size_t low;
    size_t high;
    int result;
};

// Gracias to cppreference.com!
struct BSearchResult bsearch2(
        const void *key,
        const void *base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void *p1, const void *p2, void *user),
        void *user) {
    struct BSearchResult result;
    struct BSearchResult ALL_GREATER = {0, 0, 0};
    struct BSearchResult ALL_LESS = {nmemb, nmemb, 0};
    if (nmemb == 0) return ALL_GREATER;
    if (compar(base, key, user) > 0) return ALL_GREATER;
    if (compar(base + size * (nmemb - 1), key, user) < 0) return ALL_LESS;
    // lower_bound
    int first = 0, last = nmemb;
    int count = last - first;
    while (count > 0) {
        int step = count / 2;
        int mid = first + step;
        if (compar(base + size * mid, key, user) < 0) {
            first = ++mid;
            count -= ++step;
        } else {
            count = step;
        }
    }
    result.low = first;
    // upper_bound
    first = 0, last = nmemb;
    count = last - first;
    while (count > 0) {
        int step = count / 2;
        int mid = first + step;
        if (compar(base + size * mid, key, user) <= 0) {
            first = ++mid;
            count -= ++step;
        } else {
            count = step;
        }
    }
    result.high = first;
    if (result.low == result.high) {
        result.result = 0;
    } else {
        result.result = 1;
    }
    return result;
}

