#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitInfo {
    u32 flags;
    VecFx32 contactPoint;
    VecFx32 sourcePosition;
    u8 pad_1c[0xc];
    s32 damage;
} HitInfo;

typedef struct Actor {
    u8 pad_0000[0x928];
    u64 statusFlags;
    u8 pad_0930[0x944 - 0x930];
    s32 mode;
    u8 pad_0948[4];
    VecFx32 guardPoint;
    u8 pad_0958[4];
    s32 guardTimer;
    u8 pad_0960[0x970 - 0x960];
    VecFx32 velocity;
    VecFx32 drift;
} Actor;

extern BOOL func_ov059_020c921c(Actor *actor, HitInfo *hit);
extern void func_ov021_020a78d0(Actor *actor, HitInfo *hit);
extern int func_ov021_020a768c(Actor *actor, HitInfo *hit, BOOL critical);
extern BOOL AddClampedHealth(Actor *actor, int delta);
extern void TryApplyStatusEffect(Actor *actor, HitInfo *hit);
extern void Actor_MarkGuardBreakInState3(Actor *actor);
extern u32 random_next_scaled(u32 upperBound);
extern VecFx32 func_ov021_020af8f4(fx32 radians);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void func_ov043_020bcb58(const VecFx32 *launch, int param40, int param44, int param2c);
extern void func_ov059_020cb988(Actor *actor);

BOOL Actor_TakeHit(Actor *actor, HitInfo *hit)
{
    VecFx32 contact = hit->contactPoint;
    int damage;
    BOOL knockback;

    if (func_ov059_020c921c(actor, hit)) {
        return TRUE;
    }
    if (actor->statusFlags & 0x820) {
        return FALSE;
    }
    if (!(hit->flags & 0x20)) {
        if (actor->guardTimer > 0) {
            return FALSE;
        }
        actor->guardTimer += 0x2d000;
    }
    func_ov021_020a78d0(actor, hit);
    damage = func_ov021_020a768c(actor, hit, actor->mode == 10);
    AddClampedHealth(actor, (s16)-damage);
    hit->damage = damage;
    TryApplyStatusEffect(actor, hit);
    knockback = TRUE;
    if (hit->flags & 0x10) {
        knockback = FALSE;
    }
    if (knockback) {
        int sign;
        VecFx32 launch;
        VecFx32 orbit;
        VecFx32 offset;

        actor->statusFlags |= 0x10;
        actor->guardPoint = contact;
        actor->velocity.z = 0;
        actor->velocity.y = 0;
        actor->velocity.x = 0;
        actor->drift.z = 0;
        actor->drift.y = 0;
        actor->drift.x = 0;
        Actor_MarkGuardBreakInState3(actor);
        sign = random_next_scaled(2) != 0 ? 1 : -1;
        orbit = func_ov021_020af8f4(random_next_scaled(0x6488));
        offset = orbit;
        ScaleVecFx32InPlace(&offset, 0x1ec);
        launch = offset;
        func_ov043_020bcb58(&launch, 0x333, (int)((s64)sign * 0x430), 0xa000);
        func_ov059_020cb988(actor);
    }
    return TRUE;
}
