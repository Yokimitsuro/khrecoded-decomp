#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xcab4];
    void *slots[4];
} Ov039State;

extern int ZeroHalfThenFree(void *block);

void FreeSlotPair(Ov039State *state, int slot)
{
    if (state->slots[slot] != 0) {
        ZeroHalfThenFree(state->slots[slot]);
        state->slots[slot] = 0;
    }
    slot++;
    if (state->slots[slot] != 0) {
        ZeroHalfThenFree(state->slots[slot]);
        state->slots[slot] = 0;
    }
}
