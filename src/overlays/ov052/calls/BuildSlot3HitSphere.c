#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollShape {
    void *geometry;
    VecFx32 boxMax;
    VecFx32 boxMin;
    s32 kind;
} CollShape;

typedef struct CollSphere {
    VecFx32 center;
    fx32 radius;
} CollSphere;

typedef struct HitActor {
    u8 pad_0000[0x9ac];
    u64 stateFlags;
    u8 pad_09b4[0x1038 - 0x9b4];
    CollSphere hitSphere;
} HitActor;

extern VecFx32 GetSlot3WorldPosition(HitActor *actor);
extern CollShape func_0203ad28(CollSphere *sphere, const VecFx32 *center, fx32 radius);

BOOL BuildSlot3HitSphere(HitActor *actor, CollShape *out)
{
    if (actor->stateFlags & 0x20820) {
        return FALSE;
    } else {
        VecFx32 center = GetSlot3WorldPosition(actor);
        *out = func_0203ad28(&actor->hitSphere, &center, 0x4cd);
        return TRUE;
    }
}
