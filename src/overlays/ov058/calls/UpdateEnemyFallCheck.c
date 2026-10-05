#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[2];
    u16 locked;
} EnemyStats;

typedef struct {
    u8 pad_000[0x1d4];
    EnemyStats *stats;
    u8 pad_1d8[0x9ac - 0x1d8];
    u64 stateFlags;
    u8 pad_9b4[0x9c0 - 0x9b4];
    s32 state;
    u8 pad_9c4[0xa4c - 0x9c4];
    s8 subState;
} Enemy;

extern void func_ov058_020d50cc(Enemy *enemy);
extern void CheckEnemyContactAbove(Enemy *enemy);
extern int func_ov001_02067ed4(void);
extern s8 func_ov001_02068084(void);
extern VecFx32 *func_ov052_020ceb74(Enemy *enemy);

void UpdateEnemyFallCheck(Enemy *enemy)
{
    int mode;

    if (enemy->stats->locked != 0 && (enemy->stateFlags & 0x20) != 0 && (enemy->stateFlags & 0x20000) == 0) {
        if (enemy->state == 2) {
            if (enemy->subState == 2) {
                func_ov058_020d50cc(enemy);
                return;
            }
        } else {
            CheckEnemyContactAbove(enemy);
        }
    }
    if ((enemy->stateFlags & 0x20820) != 0) {
        return;
    }
    mode = func_ov001_02067ed4();
    if (func_ov001_02068084() != 5 || mode != 5) {
        return;
    }
    if (func_ov052_020ceb74(enemy)->y <= -0x3000) {
        func_ov058_020d50cc(enemy);
    }
}
