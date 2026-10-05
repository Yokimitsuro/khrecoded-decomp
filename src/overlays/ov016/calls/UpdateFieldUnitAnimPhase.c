#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
} FieldUnit;

extern BOOL StepFieldObjectAnim(FieldUnit *unit);
extern void func_ov016_020a2c64(FieldUnit *unit);
extern void func_ov016_020a29c4(FieldUnit *unit);

BOOL UpdateFieldUnitAnimPhase(FieldUnit *unit)
{
    if ((unit->flags & 0x40) && StepFieldObjectAnim(unit)) {
        unit->flags &= ~0x40;
    }
    func_ov016_020a2c64(unit);
    if (!(unit->flags & 0x60)) {
        func_ov016_020a29c4(unit);
    }
    return FALSE;
}
