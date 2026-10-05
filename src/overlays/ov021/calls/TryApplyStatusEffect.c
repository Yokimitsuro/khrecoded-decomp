#include "nitro/types.h"

typedef struct {
    u16 pad_00;
    u16 maxHealth;
} UnitStats;

typedef struct BattleUnit BattleUnit;
struct BattleUnit {
    u8 pad_00[0x1d4];
    UnitStats *stats;
    u8 player;
    u8 pad_1d9[3];
    s32 mode;
    u8 pad_1e0[0x20];
    void (*onStatus)(BattleUnit *unit, s32 status);
    u8 pad_204[0x28];
    s32 (*getMode)(BattleUnit *unit);
};

typedef struct {
    u32 flags;
    u32 pad_04;
    s32 power;
    u8 pad_0c[0x18];
    u32 resultFlags;
    s32 drained;
    u32 pad_2c;
    s32 chance;
    s32 status;
} StatusAttack;

typedef struct {
    s32 guardFlag[14];
} StatusGuardTable;

extern const StatusGuardTable data_ov021_020b4dcc;

extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int nextRandom12(void);
extern void AddClampedHealth(BattleUnit *unit, s16 amount);

void TryApplyStatusEffect(BattleUnit *unit, StatusAttack *attack)
{
    s32 mode;
    s32 chance;
    BOOL triggered;

    if (unit->getMode != NULL) {
        mode = unit->getMode(unit);
    } else {
        mode = unit->mode;
    }
    chance = 0;
    if (IsPlayerEntryFlagSet(unit->player, 0x53)) {
        return;
    }
    if (attack->status != 0 && mode != attack->status) {
        StatusGuardTable table = data_ov021_020b4dcc;
        if (table.guardFlag[attack->status] == -1 || !IsPlayerEntryFlagSet(unit->player, table.guardFlag[attack->status])) {
            switch (attack->status) {
            case 1:
                if (unit->stats->maxHealth > 1) {
                    chance = attack->chance;
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 13:
                chance = attack->chance;
                break;
            }
            if (chance > 0 && nextRandom12() * 100 <= chance) {
                attack->resultFlags |= 2;
                if (attack->status == 13) {
                    int drain = unit->stats->maxHealth / 2;
                    if (drain < 1) {
                        drain = 1;
                    }
                    AddClampedHealth(unit, -drain);
                    attack->drained += drain;
                    return;
                }
                if (unit->onStatus != NULL) {
                    unit->onStatus(unit, attack->status);
                }
                return;
            }
        }
    }
    triggered = FALSE;
    switch (mode) {
    case 2:
        if (attack->flags & 0x80) {
            triggered = TRUE;
        }
        if (attack->power > 0) {
            triggered = TRUE;
        }
        break;
    case 4:
        triggered = TRUE;
        break;
    }
    if (triggered && unit->onStatus != NULL) {
        unit->onStatus(unit, 0);
    }
}
