#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct HitResult {
    s32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc8];
} HitResult;

typedef struct HitUnit {
    u8 pad_000[2];
    s8 phase;
    u8 pad_003;
    fx32 progress;
    u8 pad_008[0xd4 - 8];
    VecFx32 position;
} HitUnit;

typedef struct EffectSource {
    u8 pad_00[0x3c];
    s8 entryIndex;
} EffectSource;

extern void *func_ov001_0206db5c(int index);
extern HitResult func_ov021_020ab0e8(EffectSource *attacker, HitUnit *unit, VecFx32 *position, VecFx32 *offset);
extern s16 func_ov021_020ab43c(HitUnit *owner, fx32 step);

BOOL AdvanceLinkedHitUnit(EffectSource *source, HitUnit *unit, fx32 step)
{
    VecFx32 position;
    VecFx32 offset;
    func_ov001_0206db5c(source->entryIndex);
    unit->progress += step;
    position = unit->position;
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    if (unit->progress == FX32_ONE) {
        func_ov021_020ab0e8(source, unit, &position, &offset);
    }
    if (unit->phase == 1) {
        u16 finished = func_ov021_020ab43c(unit, step);
        if (finished) {
            unit->phase = -1;
        }
    }
    if (unit->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
