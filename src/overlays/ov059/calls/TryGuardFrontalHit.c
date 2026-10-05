#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef s32 (*ActorGetStateFunc)(Actor *actor);

struct Actor {
    u8 pad_0000[0x1dc];
    s32 state;
    u8 pad_01E0[0x22c - 0x1e0];
    ActorGetStateFunc getState;
    u8 pad_0230[0x928 - 0x230];
    u64 statusFlags;
    u8 pad_0930[0x944 - 0x930];
    s32 mode;
    u8 pad_0948[4];
    VecFx32 guardPoint;
    u8 pad_0958[4];
    s32 guardTimer;
    u8 pad_0960[0x1820 - 0x960];
    s32 guardStock;
};

typedef struct HitInfo {
    u32 flags;
    VecFx32 contactPoint;
    VecFx32 sourcePosition;
    u8 pad_1C[8];
    u32 resultFlags;
} HitInfo;

extern VecFx32 *Actor_GetModelPosition(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern int FX_Atan2Idx(int vertical, int horizontal);
extern u16 GetLinkedAngleOffset_020cd104(Actor *actor);

BOOL TryGuardFrontalHit(Actor *actor, HitInfo *hit)
{
    s32 state;
    VecFx32 offset;

    if ((hit->flags & 8) || (hit->flags & 0x20)) {
        return FALSE;
    }
    if (actor->statusFlags & 0x10) {
        return FALSE;
    }
    if (actor->getState != NULL) {
        state = actor->getState(actor);
    } else {
        state = actor->state;
    }
    if (state == 3) {
        return FALSE;
    }
    if (actor->mode != 6) {
        return FALSE;
    }
    VEC_Subtract(&hit->sourcePosition, Actor_GetModelPosition(actor), &offset);
    offset.y = 0;
    if (offset.x != 0 || offset.y != 0 || offset.z != 0) {
        u16 hitAngle;
        int angleDelta;

        VEC_Normalize(&offset, &offset);
        hitAngle = FX_Atan2Idx(-offset.x, -offset.z);
        angleDelta = (u16)(GetLinkedAngleOffset_020cd104(actor) - hitAngle);
        if (angleDelta > 0x5000 && angleDelta < 0xb000) {
            return FALSE;
        }
    } else {
        GetLinkedAngleOffset_020cd104(actor);
    }
    if (actor->guardTimer == 0 || actor->guardStock < 0) {
        actor->statusFlags |= 8;
    }
    hit->resultFlags |= 1;
    actor->guardPoint = hit->contactPoint;
    actor->guardTimer = 0x6000;
    return TRUE;
}
