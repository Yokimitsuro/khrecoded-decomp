#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimOwner {
    u8 pad0[2];
    s8 phase;
    u8 pad3;
    int elapsed;
    u8 pad8[0xcc];
    VecFx32 position;
} AnimOwner;

typedef struct SpawnWork {
    u8 data[0xd4];
} SpawnWork;

extern void FindStrongestHit(SpawnWork *work, void *source, AnimOwner *owner, VecFx32 *position, VecFx32 *offset);
extern int AdvanceOwnerAnimation(AnimOwner *owner, int step);
extern void AdvanceToSecondPhase(AnimOwner *owner);

BOOL UpdateAnimatedOwner(void *source, AnimOwner *owner, int step)
{
    SpawnWork work;
    VecFx32 position;
    VecFx32 offset;

    position = owner->position;
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    if (owner->elapsed == 0) {
        FindStrongestHit(&work, source, owner, &position, &offset);
    }
    owner->elapsed += step;
    if (owner->phase == 1 && (u16)AdvanceOwnerAnimation(owner, step) != 0) {
        AdvanceToSecondPhase(owner);
    }
    if (owner->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
