#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 animState[0xd8];
    u8 blendTable[1];
} EnemyModel;

typedef struct {
    u8 pad_00[2];
    u16 locked;
    u16 maxHealth;
} EnemyStats;

typedef struct {
    u8 pad_00[0x2c];
    s32 soundEmitter;
} AiState;

typedef struct {
    u8 pad_000[0x1d4];
    EnemyStats *stats;
    u8 pad_1d8[0x230 - 0x1d8];
    EnemyModel *model;
    u8 pad_234[0x9ac - 0x234];
    u64 stateFlags;
    u8 pad_9b4[0x1258 - 0x9b4];
    AiState ai;
} Enemy;

extern void func_ov021_020a75f8(Enemy *enemy, u16 value);
extern int func_ov001_0206db8c(int index);
extern void StopAndClearSoundEmitter(s32 groupId, s32 emitterIndex);
extern void selectJointAnimationBlend(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);

void FinishEnemyRecovery(Enemy *enemy)
{
    AiState *ai = &enemy->ai;
    int maxHealth = enemy->stats->maxHealth << 12;
    int emitter;

    if (enemy->stats->locked == 0) {
        int amount = ((maxHealth / 3) >> 12);
        if (amount <= 0) {
            amount = 1;
        }
        func_ov021_020a75f8(enemy, amount);
    }
    emitter = ai->soundEmitter;
    if (emitter >= 0) {
        StopAndClearSoundEmitter(func_ov001_0206db8c(8), emitter);
        ai->soundEmitter = -1;
    }
    if ((enemy->model->flags & 0x20) == 0) {
        selectJointAnimationBlend(enemy->model->animState, 3, enemy->model->blendTable, 0);
    }
    enemy->stateFlags &= ~0x41800800ULL;
}
