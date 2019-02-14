struct State
{
    int *data;
    int size;
    void (*cmp)(
            int v1,
            int v2,
            void (*sort_cc)(int result, void *sort_cntx),
            void *sort_cntx
    );
    void (*cc)(
            int *sorted_data,
            int sorted_size,
            void *user_cntx
    );
    void *user_cntx;
    int i, j;
};

void swap_cc(int result, void *cntx) {
    struct State *state = cntx;
    if (result > 0) {
        int tmp = state->data[state->j];
        state->data[state->j] = state->data[state->j + 1];
        state->data[state->j + 1] = tmp;
    }
    if (state->i + 1 == state->size) {
        // Stop the sort.
        state->cc(state->data, state->size, state->user_cntx);
    } else {
        ++state->j;
        if (state->j + state->i + 1 == state->size) {
            ++state->i;
            state->j = 0;
        }
        state->cmp(state->data[state->j], state->data[state->j + 1], swap_cc, state);
    }
}

void sort_with_cc(
        int *data,
        int size,
        void (*cmp)(
                int v1,
                int v2,
                void (*sort_cc)(int result, void *sort_cntx),
                void *sort_cntx
        ),
        void (*cc)(
                int *sorted_data,
                int sorted_size,
                void *user_cntx
        ),
        void *user_cntx
) {
    if (size <= 1) {
        cc(data, size, user_cntx);
    }
    struct State state;
    state.data = data;
    state.size = size;
    state.cmp = cmp;
    state.cc = cc;
    state.user_cntx  = user_cntx;
    state.i = 0;
    state.j = 0;

    cmp(state.data[state.j], state.data[state.j + 1], swap_cc, &state);
    for (int i = 0; i + 1 != size; ++i) {
        for (int j = 0; j != size - i - 1; ++j) {

        }
    }
    cc(data, size, user_cntx);
}

