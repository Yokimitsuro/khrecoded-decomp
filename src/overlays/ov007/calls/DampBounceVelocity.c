#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    fx32 value;
} BounceState;

BOOL DampBounceVelocity(void *unused, BounceState *state) {
    state->value = (fx32)(((s64)state->value * -0x800 + 0x800) >> 12);
    if (state->value < 0xcd) {
        state->value = 0;
        return FALSE;
    }
    return TRUE;
}
