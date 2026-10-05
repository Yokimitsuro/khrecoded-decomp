#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[6];
    u16 strength;
    u16 magic;
} PlayerStats;

typedef struct {
    fx32 power;
    u8 pad_04[0xc];
    u8 attackType;
    u8 element;
} AttackDesc;

extern void *func_ov001_0206db5c(int player);
extern BOOL func_ov001_02075248(int player);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int GetPlayerEntryCount(int player, u32 id);
extern fx32 FX_Mul(fx32 a, fx32 b);

fx32 ComputeAttackDamage(int player, AttackDesc *attack)
{
    BOOL physical;
    BOOL magical;
    PlayerStats *stats;
    fx32 damage;
    BOOL boosted;
    stats = *(PlayerStats **)((u8 *)func_ov001_0206db5c(player) + 0x1d4);
    damage = 0;
    physical = FALSE;
    magical = FALSE;
    boosted = FALSE;
    if (func_ov001_02075248(player)) {
        boosted = TRUE;
    }
    switch (attack->attackType) {
    case 0:
        damage = stats->strength << 12;
        if (boosted && IsPlayerEntryFlagSet(player, 0x1b)) {
            damage += FX_Mul(damage, 0x280);
        }
        physical = TRUE;
        break;
    case 1:
        damage = stats->magic << 12;
        if (boosted && IsPlayerEntryFlagSet(player, 0x1c)) {
            damage += FX_Mul(damage, 0x280);
        }
        magical = TRUE;
        break;
    }
    damage = FX_Mul(attack->power, damage);
    switch (attack->element) {
    case 1:
    case 2:
    case 3:
    case 4: {
        u32 id = attack->element - 1;
        if (IsPlayerEntryFlagSet(player, id)) {
            damage += damage * GetPlayerEntryCount(player, id) / 100;
        }
        break;
    }
    }
    if (physical) {
        if (IsPlayerEntryFlagSet(player, 0x48)) {
            damage += FX_Mul(damage, 0x480);
        }
        if (IsPlayerEntryFlagSet(player, 0x4f)) {
            damage += FX_Mul(damage, 0x800);
        }
    }
    if (magical && IsPlayerEntryFlagSet(player, 0x49)) {
        damage += FX_Mul(damage, 0x480);
    }
    return damage;
}
