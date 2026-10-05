#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x04];
    s32 value;
} ObjectParams;

typedef struct {
    u8 pad_00[0x84];
    s8 groupIndex;
    s8 entryIndex;
    u8 pad_86[0x0a];
    s32 baseValue;
    s8 startSlot;
    u8 pad_95[0x03];
    s32 unk_98;
    s32 unk_9c;
    s32 levels[12];
    s32 unk_d0;
} RampState;

extern void *func_ov001_0207f060(int groupIndex, int entryIndex);
extern ObjectParams *func_ov001_0207f838(void *object);
extern int _s32_div_f(int numerator, int denominator);

void BuildDescendingLevelTable(RampState *state)
{
    int slotCount = 12 - state->startSlot;
    s32 level = func_ov001_0207f838(func_ov001_0207f060(state->groupIndex, state->entryIndex))->value;
    int step = _s32_div_f(level, slotCount);
    int slot;

    for (slot = state->startSlot; slot < 12; slot++) {
        state->levels[slot] = level;
        level -= step;
    }
    state->levels[0] = state->baseValue;
    state->unk_d0 = 0;
    state->unk_9c = _s32_div_f(step, 20);
    state->unk_98 = (state->baseValue >> 1) / 16;
}
