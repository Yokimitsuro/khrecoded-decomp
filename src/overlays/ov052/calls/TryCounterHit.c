#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef int (*StateQueryFunc)(Actor *actor);

typedef struct {
    u32 flags;
    VecFx32 hitPos;
    VecFx32 pos;
    u8 pad_1c[8];
    u32 state;
} HitSource;

struct Actor {
    u8 pad_0000[0x1dc];
    int guardState;
    u8 pad_01e0[0x22c - 0x1e0];
    StateQueryFunc getGuardState;
    u8 pad_0230[0x9ac - 0x230];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0x9c0 - 0x9b5];
    int stageType;
    u8 pad_09c4[0x9e0 - 0x9c4];
    VecFx32 drift;
    u8 pad_09ec[0x9f8 - 0x9ec];
    int airTime;
    u8 pad_09fc[0x1104 - 0x9fc];
    int lockTarget;
};

extern BOOL AnySubObjectBit0Set(Actor *actor);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern void AddSessionCounter(int counter, int amount);
extern void DispatchAttackHitEvent(Actor *actor, HitSource *source);

BOOL TryCounterHit(Actor *actor, HitSource *source)
{
    BOOL guarding = FALSE;
    int guardState;
    VecFx32 dir;

    if (source->flags & 2) {
        return FALSE;
    }
    if ((source->flags & 8) || (source->flags & 0x20)) {
        return FALSE;
    }
    if (actor->stateFlags & 0x10) {
        return FALSE;
    }
    if (actor->getGuardState != NULL) {
        guardState = actor->getGuardState(actor);
    } else {
        guardState = actor->guardState;
    }
    if (guardState == 3) {
        return FALSE;
    }
    if (!AnySubObjectBit0Set(actor) || func_ov001_020645c8(0x3520)
        || !IsPlayerEntryFlagSet(actor->player, 0xb)) {
        return FALSE;
    }
    if (IsPlayerEntryFlagSet(actor->player, 0x3d) && actor->stageType == 1) {
        guarding = TRUE;
    }
    if (!guarding && actor->stageType != 9) {
        return FALSE;
    }
    VEC_Subtract(&source->pos, func_ov052_020ceb74(actor), &dir);
    dir.y = 0;
    if ((dir.x != 0 || dir.y != 0 || dir.z != 0) && !IsPlayerEntryFlagSet(actor->player, 0x16)) {
        int angle;
        int diff;
        VEC_Normalize(&dir, &dir);
        angle = (u16)FX_Atan2Idx(-dir.x, -dir.z);
        diff = (u16)(GetLinkedAngleOffset(actor) - angle);
        if (diff > 0x5000 && diff < 0xb000) {
            return FALSE;
        }
    } else {
        GetLinkedAngleOffset(actor);
    }
    if (guarding) {
        actor->stateFlags |= 0x400000;
    }
    if (actor->airTime == 0 || actor->lockTarget < 0) {
        actor->stateFlags |= 8;
    }
    source->state |= 1;
    AddSessionCounter(0x10, 1);
    actor->drift = source->hitPos;
    actor->airTime = 0x6000;
    DispatchAttackHitEvent(actor, source);
    return TRUE;
}
