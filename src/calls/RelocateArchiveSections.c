#include "nitro/types.h"

typedef struct RelocState {
    int tag;
    int relocated;
    int sections[8];
} RelocState;

extern void func_0202d0ac(void *entry, int flags);

/* Turns eight relative section offsets into pointers. */
void RelocateArchiveSections(RelocState *state, int flags, int enableDispatch)
{
    int i;

    if (state->relocated != 0) {
        return;
    }
    i = 0;
    do {
        if (state->sections[i] != -1) {
            unsigned int entryIndex;
            state->sections[i] = (int)((char *)state + state->sections[i]);
            entryIndex = 0;
            while (entryIndex < *(unsigned int *)state->sections[i]) {
                ((int *)state->sections[i])[entryIndex + 1] =
                    (int)((char *)state + ((int *)state->sections[i])[entryIndex + 1]);
                if (enableDispatch != 0 && state->tag == 0x4850414b && i == 7) {
                    func_0202d0ac((void *)((int *)state->sections[i])[entryIndex + 1], flags);
                }
                entryIndex = entryIndex + 1;
            }
        } else {
            state->sections[i] = 0;
        }
        i = i + 1;
    } while (i < 8);
    state->relocated = state->relocated + 1;
}
