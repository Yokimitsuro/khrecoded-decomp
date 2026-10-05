#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Collider {
    u8 pad_00[0xc];
    u8 flags;
    u8 pad_0d[0x6c - 0x0d];
    s32 state;
} Collider;

typedef struct CollisionHit {
    u8 pad_00[0x10];
    Collider *collider;
} CollisionHit;

typedef struct GroundActor {
    u8 pad_000[0x28c];
    u16 unk_28C_0 : 7;
    u16 groundProbeMode : 4;
    u16 unk_28C_11 : 5;
    u8 pad_28e[2];
    fx32 groundHeight;
    u8 pad_294[0x32c - 0x294];
    fx32 probeDistance;
} GroundActor;

extern CollisionHit *func_ov001_02091698(GroundActor *actor, const VecFx32 *origin, const VecFx32 *target,
                                         VecFx32 *hitPosition, fx32 distance);

CollisionHit *ProbeActorGround(GroundActor *actor, const VecFx32 *origin, VecFx32 *hitPosition)
{
    CollisionHit *hit;
    Collider *collider;
    BOOL ignoreHit;

    if (actor->groundProbeMode == 0) {
        return NULL;
    }
    ignoreHit = FALSE;
    hit = func_ov001_02091698(actor, origin, NULL, hitPosition, actor->probeDistance);
    if (hit != NULL) {
        collider = hit->collider;
        if (collider != NULL) {
            if (collider->flags & 2) {
                ignoreHit = TRUE;
            }
            if (collider->state == 5) {
                ignoreHit = TRUE;
            }
            if (ignoreHit) {
                actor->groundHeight = -0x3000;
                return NULL;
            }
        }
        actor->groundHeight = hitPosition->y;
    }
    return hit;
}
