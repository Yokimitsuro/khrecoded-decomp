#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef int (*EnemyHandler)(Enemy *enemy);
typedef void (*EnemyCallback)(Enemy *enemy, int value);

typedef struct {
    u32 flags;
    u8 animState[0xd8];
    u8 blendTable[1];
} EnemyModel;

typedef struct {
    s32 mode;
    u32 flags;
    u8 pad_08[0x0c];
    s32 timer;
    u8 pad_18[0x14];
    s32 effectHandle;
} AiState;

typedef struct {
    u8 kind;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[2];
    s16 angle;
    u8 pad_14[0x10];
    u8 flagA;
    u8 flagB;
    u16 count;
    u8 pad_28[4];
} EffectParams;

typedef struct {
    VecFx32 offsets[2];
} EffectOffsetTable;

typedef struct {
    EnemyHandler handler;
    s32 state;
} EnemyStateSlot;

struct Enemy {
    u8 pad_000[0x1f8];
    EnemyCallback onEnterState;
    EnemyCallback onFlagCallback;
    EnemyCallback onLeaveState;
    u8 pad_204[0x230 - 0x204];
    EnemyModel *model;
    u8 pad_234[0x338 - 0x234];
    s32 moveMode;
    u8 pad_33c[0x768 - 0x33c];
    s32 isActive;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 effectKind;
    u8 pad_9b5[3];
    s32 spawnIndex;
    EnemyStateSlot stateSlot;
    u8 pad_9c4[4];
    VecFx32 moveTotal;
    u8 pad_9d4[0x0c];
    VecFx32 moveDelta;
    u8 pad_9ec[0xa38 - 0x9ec];
    s32 unkA38;
    u8 pad_a3c[0x1258 - 0xa3c];
    AiState ai;
};

extern const EffectOffsetTable data_ov058_020d8978;

extern void func_ov058_020d546c(Enemy *enemy);
extern void func_ov058_020d50cc(Enemy *enemy);
extern int UpdateEnemyDownState(Enemy *enemy);
extern int func_ov058_020d5488(Enemy *enemy);
extern int UpdateEnemyApproachState(Enemy *enemy);
extern int ExitActorState(Enemy *enemy, int state, int force);
extern int func_ov052_020cd358(Enemy *enemy, int state);
extern s16 GetLinkedAngleOffset(Enemy *enemy);
extern void selectJointAnimationBlend(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void ResetAnimationTrackState(EffectParams *params);
extern s32 func_ov021_020a8cc0(EffectParams *params, int arg);
extern int func_ov001_0206db8c(int index);
extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_020645dc(u32 value);

int ChangeEnemyState(Enemy *enemy, int state)
{
    AiState *ai = &enemy->ai;
    EnemyStateSlot *slot = &enemy->stateSlot;
    int result = slot->state;

    switch (state) {
    case 10:
        ai->flags &= ~0x80000;
        func_ov058_020d546c(enemy);
        result = func_ov052_020cd358(enemy, state);
        break;
    case 14:
        break;
    case 15:
        if ((enemy->stateFlags & 0x10) != 0) {
            break;
        }
        if (result == 10 && enemy->isActive == 0) {
            break;
        }
        if (ExitActorState(enemy, state, 0) != 0) {
            break;
        }
        if (enemy->onLeaveState != NULL) {
            enemy->onLeaveState(enemy, 0);
        }
        enemy->stateFlags &= ~0x240000ULL;
        enemy->stateFlags |= 0x1000000;
        enemy->stateFlags |= 0x800;
        if (enemy->onEnterState != NULL) {
            enemy->onEnterState(enemy, 10);
        }
        if ((enemy->model->flags & 0x20) == 0) {
            selectJointAnimationBlend(enemy->model->animState, 3, enemy->model->blendTable, 1);
        }
        if ((enemy->stateFlags & 0x40000000) != 0 && enemy->onFlagCallback != NULL) {
            enemy->onFlagCallback(enemy, 0x3000);
        }
        enemy->stateFlags |= 0x40000000;
        ai->flags &= ~0x80000;
        func_ov058_020d546c(enemy);
        enemy->moveTotal.z = 0;
        enemy->moveTotal.y = 0;
        enemy->moveTotal.x = 0;
        enemy->moveDelta.z = 0;
        enemy->moveDelta.y = 0;
        enemy->moveDelta.x = 0;
        if (enemy->moveMode == 0) {
            func_ov058_020d50cc(enemy);
            ai->timer = 0xf000;
            break;
        }
        {
            EffectParams params;
            EffectOffsetTable offsets = data_ov058_020d8978;
            int index;

            ResetAnimationTrackState(&params);
            params.kind = enemy->effectKind;
            params.count = 4;
            params.flagA = 0;
            params.flagB = 1;
            params.angle = GetLinkedAngleOffset(enemy) + 0x8000;
            index = enemy->spawnIndex - 1;
            params.position = offsets.offsets[index];
            ai->effectHandle = func_ov021_020a8cc0(&params, func_ov001_0206db8c(8));
        }
        if (func_ov001_02064784() == 5 && func_ov001_020645c8(0x3701) == 0) {
            func_ov001_020645dc(0x3701);
        }
        slot->handler = UpdateEnemyDownState;
        result = 15;
        slot->state = result;
        break;
    case 2:
        enemy->unkA38 = 0;
        result = func_ov052_020cd358(enemy, 0x12);
        slot->state = result;
        break;
    case 30:
        ExitActorState(enemy, state, 1);
        func_ov058_020d546c(enemy);
        slot->handler = func_ov058_020d5488;
        result = 30;
        slot->state = result;
        break;
    case 32:
        ExitActorState(enemy, state, 1);
        func_ov058_020d546c(enemy);
        slot->handler = UpdateEnemyApproachState;
        result = 32;
        slot->state = result;
        break;
    default:
        result = func_ov052_020cd358(enemy, state);
        break;
    }
    return result;
}
