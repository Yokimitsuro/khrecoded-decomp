#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s16 motionId;
} MotionInfo;

typedef struct {
    u8 pad_00[0x76];
    s8 enabled;
    u8 pad_77[0xbd - 0x77];
    u8 lowBits : 4;
    u8 state : 4;
    u8 pad_be[0xec - 0xbe];
    MotionInfo *motion;
} FieldUnit;

extern void EnterFieldUnitPhase5(FieldUnit *unit, BOOL doReset);

void TryEnterFieldUnitPhase5(FieldUnit *unit, int selection)
{
    if (unit->enabled != 0) {
        if (unit->state >= 5 && unit->motion->motionId == -1) {
            return;
        }
        EnterFieldUnitPhase5(unit, selection != 0xff);
    }
}
