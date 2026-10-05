typedef struct {
    int tag;
    int counter;
    int *sections[8];
} ResGroup;

extern void NNS_G3dResDefaultRelease(void *pResData);

void func_0202d34c(ResGroup *state)
{
    int i, j;

    if (state->counter == 0) {
        return;
    }
    state->counter = state->counter - 1;
    if (state->counter == 0 && state->tag == 0x4850414b) {
        for (i = 0; i < 8; i++) {
            if (state->sections[i] != 0) {
                j = 0;
                while (j < *(unsigned int *)state->sections[i]) {
                    if (i == 7) {
                        NNS_G3dResDefaultRelease((void *)state->sections[i][j + 1]);
                    }
                    j = j + 1;
                }
            }
        }
    }
}
