#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1d4];
    u8 *unk_1d4;
} BigObject;

typedef struct {
    u8 pad_000[0x178];
    s32 baseValue;
    u8 pad_17c[0x20];
    s8 bonusPercent;
} Actor;

extern BigObject *GetBoundedEntryField(u32 handle);
extern s32 _s32_div_f(s32 numerator, s32 denominator);
extern s32 func_ov001_02075248(u32 handle);
extern s32 IsPlayerEntryFlagSet(u32 handle, s32 flag);
extern s32 GetPlayerEntryCount(u32 handle, s32 flag);
extern s32 FX_Mul(s32 left, s32 right);
extern void AddClampedHealth(BigObject *entity, s32 value);

/* Computes a level-scaled bonus value and applies it. */
void ComputeAndApplyLevelScaledValue(Actor *actor, u32 handle)
{
    s32 flag;
    s32 bonus;
    BigObject *entity = GetBoundedEntryField(handle);
    s32 levelFactor = (u32)*(u16 *)(entity->unk_1d4 + 8) * 0x1000;
    s32 scaledBase = _s32_div_f(actor->baseValue * (actor->bonusPercent + 100), 100);

    flag = func_ov001_02075248(handle);
    if ((flag != 0) && (flag = IsPlayerEntryFlagSet(handle, 0x1c), flag != 0)) {
        bonus = FX_Mul(levelFactor, 0x280);
        levelFactor = levelFactor + bonus;
    }
    scaledBase = FX_Mul(scaledBase, levelFactor);
    flag = IsPlayerEntryFlagSet(handle, 4);
    if (flag != 0) {
        bonus = GetPlayerEntryCount(handle, 4);
        bonus = _s32_div_f(scaledBase * bonus, 100);
        scaledBase = scaledBase + bonus;
    }
    flag = IsPlayerEntryFlagSet(handle, 0x49);
    if (flag != 0) {
        bonus = FX_Mul(scaledBase, 0x480);
        scaledBase = scaledBase + bonus;
    }
    AddClampedHealth(entity, (scaledBase << 4) >> 0x10);
}
