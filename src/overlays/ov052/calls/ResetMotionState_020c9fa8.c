#include "nitro/types.h"

typedef struct {
    int field0;
    int field4;
    int field8;
    int fieldC;
    int field10;
    int field14;
    int field18;
    u16 field1C;
    u16 scale;
    u8 pad[0x14];
    int field34;
    int field38;
    s8 indexA;
    u8 pad3D;
    s8 indexB;
} MotionState;

void ResetMotionState_020c9fa8(MotionState *state)
{
    state->field4 = 0;
    state->field8 = 0;
    state->fieldC = 0;
    state->field1C = 0;
    state->scale = 0x2000;
    state->indexA = -1;
    state->indexB = -1;
    state->field34 = 0;
    state->field38 = 0;
    state->field18 = 0;
    state->field14 = 0;
    state->field10 = 0;
    state->field0 = 0;
}
