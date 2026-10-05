#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef void (*EnemyStateCallback)(Enemy *enemy, int state, int arg);
typedef void (*EnemyCallback)(Enemy *enemy, int value);

typedef struct {
    u32 flags;
    u8 animState[0xd8];
    u8 blendTable[1];
} EnemyModel;

typedef struct {
    u8 kind;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[2];
    s16 angle;
    u8 pad_14[0x10];
    u8 flagA;
    u8 flagB;
    u8 pad_26[6];
} EffectParams;

typedef struct {
    u8 pad_00[0x2c];
    s32 soundEmitter;
} AiState;

struct Enemy {
    u8 pad_000[0x1f8];
    EnemyStateCallback onEnterState;
    u8 pad_1fc[0x230 - 0x1fc];
    EnemyModel *model;
    u8 pad_234[0x75c - 0x234];
    s32 animId;
    u8 pad_760[8];
    s32 animDone;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 effectKind;
    u8 pad_9b5[0x10ec - 0x9b5];
    EnemyCallback onNotify;
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern int func_ov001_0206db8c(int index);
extern void StopAndClearSoundEmitter(s32 groupId, s32 emitterIndex);
extern void ResetAnimationTrackState(EffectParams *params);
extern s16 func_ov021_020a8cc0(EffectParams *params, int group);
extern u16 func_ov052_020ceb9c(Enemy *enemy);
extern void selectJointAnimationBlend(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void FinishEnemyRecovery(Enemy *enemy);

void UpdateEnemyDownState(Enemy *enemy)
{
    AiState *ai = &enemy->ai;
    EffectParams params;

    if ((enemy->stateFlags & 0x800000) == 0) {
        return;
    }
    if (enemy->animId != 0xd) {
        StopAndClearSoundEmitter(func_ov001_0206db8c(8), ai->soundEmitter);
        ai->soundEmitter = -1;
        ResetAnimationTrackState(&params);
        params.kind = enemy->effectKind;
        params.flagB = 1;
        params.flagA = 0;
        params.angle = func_ov052_020ceb9c(enemy) + 0x8000;
        func_ov021_020a8cc0(&params, func_ov001_0206db8c(9));
        if (enemy->onEnterState != NULL) {
            enemy->onEnterState(enemy, 0xd, -1);
        }
        if ((enemy->model->flags & 0x20) == 0) {
            selectJointAnimationBlend(enemy->model->animState, 3, enemy->model->blendTable, 2);
        }
    } else if (enemy->animDone != 0) {
        enemy->onNotify(enemy, 1);
        if (enemy->onEnterState != NULL) {
            enemy->onEnterState(enemy, 0, -1);
        }
        FinishEnemyRecovery(enemy);
    }
}
