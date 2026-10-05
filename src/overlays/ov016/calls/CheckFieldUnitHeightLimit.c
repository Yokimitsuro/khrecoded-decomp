#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x34];
    fx32 speedField;
    u8 pad_38[4];
    fx32 posY;
    u8 pad_40[0xc0 - 0x40];
    u32 stateFlags;
} FieldUnit;

extern void func_ov016_020a229c(FieldUnit *unit, int arg);

void CheckFieldUnitHeightLimit(FieldUnit *unit)
{
    if (unit->posY + 0x1800 < 0x80) {
        func_ov016_020a229c(unit, 0);
        unit->stateFlags |= 0x1000000;
        unit->speedField = 0x800;
    }
}
