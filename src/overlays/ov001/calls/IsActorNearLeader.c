#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldActor {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x154];
    u32 (*getStateFlags)(struct FieldActor *actor);
} FieldActor;

extern VecFx32 *func_ov001_0206dc4c(int partyIndex);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsActorNearLeader(FieldActor *actor, fx32 range)
{
    u32 stateFlags = 0;
    VecFx32 *leaderPos = func_ov001_0206dc4c(0);
    VecFx32 position = actor->position;
    fx32 distance;

    if (actor->getStateFlags != NULL) {
        stateFlags = actor->getStateFlags(actor);
    }
    if (!(stateFlags & 2)) {
        return FALSE;
    }
    distance = VEC_Distance(&position, leaderPos);
    if (distance > range || distance > 0x1800) {
        return FALSE;
    }
    return TRUE;
}
