#include "nitro/types.h"
#include "nitro/fx_types.h"
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

extern HitResult FindStrongestHit(void *attacker, HitUnit *unit, VecFx32 *position, VecFx32 *offset);
extern s16 AdvanceOwnerAnimation(HitUnit *owner, fx32 step);
extern void AdvanceToSecondPhase(HitUnit *unit);

BOOL AdvanceHitUnit(void *attacker, HitUnit *unit, fx32 step)
{
    VecFx32 position = unit->position;
    VecFx32 offset;
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    unit->progress += step;
    if (unit->progress == FX32_ONE) {
        FindStrongestHit(attacker, unit, &position, &offset);
    }
    if (unit->phase == 1 && AdvanceOwnerAnimation(unit, step)) {
        AdvanceToSecondPhase(unit);
    }
    if (unit->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
