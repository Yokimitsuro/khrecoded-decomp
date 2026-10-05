#include "nitro/types.h"
#include "nitro/fx_types.h"

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
    u8 pad_0e0[0x13e - 0xe0];
    s16 hitTargets[8];
} HitUnit;

typedef struct EntryInfo {
    u8 pad_000[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct EffectSource {
    u8 pad_00[0x3c];
    s8 entryIndex;
} EffectSource;

extern EntryInfo *func_ov001_0206db5c(int index);
extern HitResult func_ov021_020ab0e8(EffectSource *attacker, HitUnit *unit, VecFx32 *position, VecFx32 *offset);
extern s16 func_ov021_020ab43c(HitUnit *owner, fx32 step);

BOOL AdvancePulsingHitUnit(EffectSource *source, HitUnit *unit, fx32 step)
{
    EntryInfo *entry = func_ov001_0206db5c(source->entryIndex);
    VecFx32 position;
    VecFx32 offset;
    int i;

    unit->progress += step;
    position = entry->position;
    unit->position = position;
    i = 0;
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    if (unit->progress % 0x3000 == 0) {
        position.y += 0x2800;
        func_ov021_020ab0e8(source, unit, &position, &offset);
        for (; i < 8; i++) {
            unit->hitTargets[i] = -1;
        }
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
