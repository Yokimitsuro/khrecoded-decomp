#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x34];
    int liftFrame;
    fx32 liftSpeed;
    u8 pad_3c[0x10];
    u16 kind : 2;
    u16 lifted : 1;
    u16 airborne : 1;
    u16 reserved4 : 2;
    u16 mirrored : 1;
    u16 blendMode : 2;
} AnimSet;

typedef struct {
    u8 pad_0000[0x760];
    int frame;
    u8 pad_0764[4];
    BOOL modeChangePending;
    u8 pad_076c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 pad_09b4[0x9c8 - 0x9b4];
    VecFx32 velocity;
    u8 pad_09d4[0x1030 - 0x9d4];
    int linkedTarget;
} Actor;

extern s32 GetLongestTrackDuration(AnimSet *set);
extern void ComputeRootMotionDelta(Actor *actor, VecFx32 *out);
extern BOOL GetLockTargetPosition(Actor *actor, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ComputeApproachStep(VecFx32 *out, Actor *actor, VecFx32 *delta, AnimSet *set, BOOL unmirrored);

void ApplyAnimRootMotion(Actor *actor, AnimSet *set)
{
    BOOL lift = FALSE;
    BOOL mirrored;
    BOOL finished = FALSE;
    BOOL blending;
    VecFx32 delta;
    VecFx32 offset;

    mirrored = set->mirrored;

    if (set->blendMode != 0) {
        blending = TRUE;
    } else {
        blending = FALSE;
    }
    if (actor->frame <= GetLongestTrackDuration(set)) {
        finished = TRUE;
    }
    if (set->blendMode != 0) {
        mirrored = TRUE;
        if (set->blendMode != 2) {
            mirrored = FALSE;
        }
    }
    ComputeRootMotionDelta(actor, &delta);
    if (GetLockTargetPosition(actor, &offset)) {
        VEC_Add(&delta, &offset, &delta);
    }
    if (actor->modeChangePending) {
        actor->velocity.x += delta.x;
        actor->velocity.z += delta.z;
        return;
    }
    ComputeApproachStep(&delta, actor, &delta, set, mirrored == FALSE ? TRUE : FALSE);
    if (actor->linkedTarget != 0) {
        lift = TRUE;
    }
    if (finished) {
        lift = TRUE;
    }
    if (mirrored || blending) {
        lift = TRUE;
    }
    if (set->kind == 1) {
        return;
    }
    if (lift && !set->lifted && delta.y != 0 && !set->lifted) {
        actor->velocity.y = delta.y;
        set->airborne = TRUE;
        actor->stateFlags |= 0x80000;
    }
    if (!set->lifted && actor->frame >= set->liftFrame && set->liftFrame >= 0) {
        set->lifted = TRUE;
        set->airborne = TRUE;
        actor->stateFlags |= 0x80000;
        actor->velocity.y = set->liftSpeed;
    }
    actor->velocity.x += delta.x;
    actor->velocity.z += delta.z;
}
