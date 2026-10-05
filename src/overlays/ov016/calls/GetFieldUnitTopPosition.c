#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x30];
    u16 flags;
    u8 pad_32[0x38 - 0x32];
    VecFx32 position;
    u8 pad_44[0x78 - 0x44];
    VecFx32 topPosition;
    u8 pad_84[0xbe - 0x84];
    u8 lowBits : 4;
    u8 phase : 4;
    u8 pad_bf;
    u32 stateFlags;
} FieldUnit;

VecFx32 *GetFieldUnitTopPosition(FieldUnit *unit)
{
    if (!(unit->stateFlags & 0x10) && (unit->flags & 8) && unit->phase == 0) {
        unit->topPosition = unit->position;
        unit->topPosition.y += 0x600;
        return &unit->topPosition;
    }
    return NULL;
}
