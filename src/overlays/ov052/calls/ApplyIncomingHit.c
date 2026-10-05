#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    VecFx32 hitPos;
    VecFx32 pos;
    int gaugeBonus;
    u8 pad_20[4];
    u32 result;
    int damage;
} HitSource;

typedef struct {
    u8 pad_00[2];
    u16 gauge;
} ActorInfo;

typedef struct {
    u8 pad_000[0x214];
    u32 pad_bits : 12;
    u32 paused : 1;
} SessionState;

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);
typedef void (*EffectCallback)(Actor *actor, int a, int b, int c);

struct Actor {
    u8 pad_0000[0x1d4];
    ActorInfo *info;
    u8 pad_01d8[4];
    int state;
    u8 pad_01e0[0x1f0 - 0x1e0];
    EffectCallback onEffect;
    u8 pad_01f4[0x22c - 0x1f4];
    StateGetter getState;
    u8 pad_0230[0x9ac - 0x230];
    u64 flags;
    u8 player;
    u8 pad_09b5[0x9c0 - 0x9b5];
    int stageType;
    u8 pad_09c4[4];
    fx32 velX;
    fx32 velY;
    fx32 velZ;
    u8 pad_09d4[0x9e0 - 0x9d4];
    VecFx32 knockback;
    u8 pad_09ec[0x9f8 - 0x9ec];
    int recoverTime;
};

extern SessionState *data_ov001_020a0480;
extern BOOL func_ov052_020c9a3c(Actor *actor, HitSource *source);
extern BOOL TryFlagTargetBehind(Actor *actor, HitSource *source);
extern BOOL func_ov052_020c9cd8(Actor *actor, HitSource *source);
extern void func_ov021_020a78d0(Actor *actor, HitSource *source);
extern int func_ov021_020a768c(Actor *actor, HitSource *source, BOOL weak);
extern void AddClampedHealth(Actor *actor, s16 amount);
extern void TryApplyStatusEffect(Actor *actor, HitSource *source);
extern BOOL func_ov001_02075248(int player);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void UseFirstAvailableMember(Actor *actor);
extern void ApplyScaledHealthDelta(Actor *actor, s32 amount, BOOL force);
extern void func_ov001_020734f8(void);
extern int func_ov001_02063b68(int index);
extern int nextRandom12(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void func_ov001_02063a80(int index, int amount);
extern void func_ov052_020cfda4(Actor *actor);
extern void AwardPartyGaugePoints(int player, int points);

BOOL ApplyIncomingHit(Actor *actor, HitSource *source)
{
    VecFx32 hitPos = source->hitPos;
    u64 flags;
    BOOL knocked;
    int damage;
    BOOL grounded;
    int state;

    source->result = 0;
    source->damage = 0;
    flags = actor->flags;
    knocked = TRUE;
    if (flags & 0x11000000) {
        source->result |= 4;
        return FALSE;
    }
    if (!(source->flags & 0x400)) {
        int stageType;
        if (flags & 0x100020820ULL) {
            return FALSE;
        }
        if (func_ov052_020c9a3c(actor, source)) {
            return TRUE;
        }
        if (TryFlagTargetBehind(actor, source)) {
            return FALSE;
        }
        if (func_ov052_020c9cd8(actor, source)) {
            return TRUE;
        }
        if (data_ov001_020a0480->paused) {
            return FALSE;
        }
        if (!(source->flags & 0x20)) {
            if (actor->recoverTime > 0) {
                source->result |= 4;
                return FALSE;
            }
            if (!(source->flags & 0x100)) {
                actor->recoverTime += 0x14000;
            }
        }
        func_ov021_020a78d0(actor, source);
        damage = func_ov021_020a768c(actor, source, actor->stageType == 10);
        AddClampedHealth(actor, -damage);
        source->damage = damage;
        TryApplyStatusEffect(actor, source);
        if (actor->info->gauge != 0) {
            if (func_ov001_02075248(actor->player) && IsPlayerEntryFlagSet(actor->player, 0x56)) {
                UseFirstAvailableMember(actor);
            }
        } else if (IsPlayerEntryFlagSet(actor->player, 0x4d)) {
            ApplyScaledHealthDelta(actor, 0x19000, TRUE);
            if (actor->onEffect != NULL) {
                actor->onEffect(actor, 0, 0xd, 0);
            }
            func_ov001_020734f8();
        }
        if (source->flags & 0x10) {
            knocked = FALSE;
        }
        stageType = actor->stageType;
        if (IsPlayerEntryFlagSet(actor->player, 0x4a) && stageType == 0xb) {
            knocked = FALSE;
        }
        if (IsPlayerEntryFlagSet(actor->player, 0x4b) && stageType == 0x1a) {
            knocked = FALSE;
        }
        if (damage > 0 && !(source->flags & 0x200)) {
            int count = func_ov001_02063b68(1);
            if (count > 0) {
                int amount;
                if (actor->info->gauge != 0) {
                    amount = FX_Mul(0x14, nextRandom12());
                    amount *= count;
                } else {
                    amount = count << 11;
                }
                amount = (amount + 0xfff) >> 12;
                if (amount <= 0) {
                    amount = 1;
                }
                func_ov001_02063a80(1, -amount);
            }
        }
    }
    grounded = FALSE;
    if (actor->getState != NULL) {
        state = actor->getState(actor);
    } else {
        state = actor->state;
    }
    if (state == 4) {
        knocked = TRUE;
        grounded = TRUE;
    }
    if (knocked) {
        actor->flags |= 0x10;
        actor->knockback = hitPos;
        actor->velZ = 0;
        actor->velY = 0;
        actor->velX = 0;
        if (grounded) {
            actor->velY = 0x580;
        }
        func_ov052_020cfda4(actor);
        if (source->flags & 0x400) {
            actor->flags |= 0x800000000ULL;
        }
    }
    if (source->gaugeBonus > 0 && IsPlayerEntryFlagSet(actor->player, 0x21)) {
        AwardPartyGaugePoints(actor->player, 0);
    }
    return TRUE;
}
