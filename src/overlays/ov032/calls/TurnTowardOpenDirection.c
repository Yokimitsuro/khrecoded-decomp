#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[2];
    s8 radius;
    s8 direction;
} MoverState;

typedef struct {
    u8 pad_00[4];
    void *object;
} Mover;

extern MoverState *func_ov032_020bbc98(void *mover);
extern unsigned int func_0202a9e4(unsigned int range);
extern int func_ov032_020bcb94(void *object, int radius, const VecFx32 *origin, fx32 height, int startDirection, u32 blockedMask);

BOOL TurnTowardOpenDirection(Mover *mover, const VecFx32 *origin, fx32 height)
{
    MoverState *state = func_ov032_020bbc98(mover);
    int roll = func_0202a9e4(16);
    int current = state->direction;
    int start = (current + roll) % 16;
    int found = func_ov032_020bcb94(mover->object, state->radius, origin, height, start,
                                                   (1 << current) | (1 << ((current + 8) % 16)));
    if (found != -1) {
        state->direction = found;
        return TRUE;
    }
    state->direction = start;
    return FALSE;
}
