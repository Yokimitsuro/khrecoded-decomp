#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 maxHealth;
} EnemyStats;

typedef struct Enemy Enemy;
struct Enemy {
    u8 pad_000[0x1d4];
    EnemyStats *stats;
    u8 pad_1d8[0x200 - 0x1d8];
    void (*resetCallback)(Enemy *enemy, int arg);
    u8 pad_204[0x21c - 0x204];
    u32 (*flagsCallback)(Enemy *enemy);
    u8 pad_220[0x9ac - 0x220];
    u64 stateFlags;
};

extern void func_ov021_020a75f8(Enemy *enemy, u16 value);

void RestoreEnemyHealthAndReset(Enemy *enemy)
{
    u32 flags;

    if (enemy->flagsCallback == NULL) {
        flags = 0;
    } else {
        flags = enemy->flagsCallback(enemy);
    }
    if (flags & 2) {
        enemy->stateFlags |= 0x800000;
    }
    func_ov021_020a75f8(enemy, enemy->stats->maxHealth);
    if (enemy->resetCallback != NULL) {
        enemy->resetCallback(enemy, 0);
    }
}
