#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0xbe - 0x44];
    u8 lowBits : 4;
    u8 phase : 4;
    u8 pad_bf;
    u32 flags;
} FieldUnit;

extern void func_ov016_020a2b28(FieldUnit *unit);
extern void func_ov016_020a2c2c(FieldUnit *unit);
extern void func_ov016_020a298c(FieldUnit *unit, BOOL doReset);
extern void SpawnSoundSlot(int bank, int id, VecFx32 *position, int flags);

void EnterFieldUnitPhase5(FieldUnit *unit, BOOL doReset)
{
    unit->phase = 5;
    func_ov016_020a2b28(unit);
    unit->flags |= 0x40;
    func_ov016_020a2c2c(unit);
    func_ov016_020a298c(unit, doReset);
    SpawnSoundSlot(0, 0x2d, &unit->position, 0);
}
