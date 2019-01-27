#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MODULO = 1ULL << 31, INCREMENT = 12345, MULTIPLIER = 1103515245 };

typedef struct RandomGenerator RandomGenerator;

typedef int(*int_funcptr_t)(RandomGenerator *);
typedef void(*void_funcptr_t)(RandomGenerator *);

typedef struct RandomOperations
{
    int_funcptr_t next;
    void_funcptr_t destroy;
} RandomOperations;

typedef struct RandomGenerator
{
    uint64_t modulo, increment, multiplier;
    uint64_t state;
    RandomOperations *ops;
} RandomGenerator;


int next_(RandomGenerator *rr) {
    uint64_t new_state = (rr->multiplier * rr->state + rr->increment) % rr->modulo;
    rr->state = new_state;
    return (int)new_state;
}

void destroy_(RandomGenerator *rr) {
    if (rr) {
        if (rr->ops) {
            free(rr->ops);
        }
        free(rr);
    }
}

RandomGenerator *random_create(uint64_t seed) {
    RandomGenerator *new_generator = malloc(sizeof(RandomGenerator));
    if (new_generator) {
        new_generator->modulo = MODULO;
        new_generator->increment = INCREMENT;
        new_generator->multiplier = MULTIPLIER;
        new_generator->state = seed;
        new_generator->ops = malloc(sizeof(RandomOperations));
        if (new_generator->ops) {
            new_generator->ops->next = &next_;
            new_generator->ops->destroy = &destroy_;
            return new_generator;
        } else {
            free(new_generator);
            return NULL;
        }
    } else {
        return NULL;
    }
}

int main() {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
      printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);

    return 0;
}

