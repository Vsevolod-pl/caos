#include <stdio.h>

struct Data
{
    unsigned U;
    int V;
    unsigned W[4];
    int X;
};

extern long long process(const struct Data *p, int i);

int main() {
    struct Data data = {
        4294967295,
        2147483647,
        {4294967295, 4294967294, 4294967293, 4294967292},
        2147483647
    };
    int i;
    if (scanf("%d", &i) == 1) {
        printf("%lld\n", process(&data, i));
        printf("%lld\n", (long long)((unsigned long long)data.U * (unsigned long long)data.W[i] + (long long)data.V * (long long)data.X));
    }
}

