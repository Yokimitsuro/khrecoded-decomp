#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef void (*EnemyCallback)(Enemy *enemy, int value);

typedef struct {
    u8 kind;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flagA;
    u8 flagB;
    u8 pad_26[6];
} EffectParams;

typedef struct {
    u8 pad_00[2];
    u16 locked;
} EnemyStats;

typedef struct {
    u8 pad_00[0x14];
    s32 timer;
    u8 pad_18[0x12];
    s16 effectHandle;
} AiState;

struct Enemy {
    u8 pad_000[0x1d4];
    EnemyStats *stats;
    u8 pad_1d8[0x200 - 0x1d8];
    EnemyCallback onLeaveState;
    u8 pad_204[0x230 - 0x204];
    void *model;
    u8 pad_234[0x9ac - 0x234];
    u64 stateFlags;
    u8 effectKind;
    u8 pad_9b5[0x10ec - 0x9b5];
    EnemyCallback onNotify;
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern void func_ov021_020a8ad4(EffectParams *params);
extern s16 func_ov021_020a8cc0(EffectParams *params, int group);
extern int func_ov001_0206db8c(int index);
extern VecFx32 *func_ov052_020ceb74(Enemy *enemy);
extern void FinishEnemyRecovery(Enemy *enemy);
extern void Obj_RemoveFromQuadTree(void *object);

void StartEnemyLaunch(Enemy *enemy)
{
    AiState *ai = &enemy->ai;

    enemy->onNotify(enemy, 0x20);
    if ((enemy->stateFlags & 0x20000) == 0) {
        EffectParams params;

        func_ov021_020a8ad4(&params);
        params.kind = enemy->effectKind;
        params.flagB = 0;
        params.flagA = 0;
        params.position = *func_ov052_020ceb74(enemy);
        ai->effectHandle = func_ov021_020a8cc0(&params, func_ov001_0206db8c(7));
    }
    if (enemy->onLeaveState != NULL) {
        enemy->onLeaveState(enemy, 0);
    }
    enemy->stateFlags &= ~0x10ULL;
    if (enemy->stats->locked == 0) {
        FinishEnemyRecovery(enemy);
    }
    enemy->stateFlags |= 0x20000;
    enemy->stateFlags |= 0x1040000;
    ai->timer = 0;
    Obj_RemoveFromQuadTree(enemy->model);
}
