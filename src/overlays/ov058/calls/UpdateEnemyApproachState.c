#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef void (*EnemyCallback)(Enemy *enemy, int value, int arg);
typedef void (*EnemyNotify)(Enemy *enemy, int value);

typedef struct {
    s32 mode;
    u32 flags;
    u8 pad_08[0x0c];
    s32 timer;
    u8 pad_18[0x12];
    s16 targetIndex;
} AiState;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flagA;
    u8 flagB;
    u8 pad_26[6];
} TrackRequest;

struct Enemy {
    u8 pad_000[0x1f8];
    EnemyCallback onEnterState;
    EnemyNotify onAnimDone;
    u8 pad_200[0x210 - 0x200];
    EnemyNotify onTurn;
    u8 pad_214[0x230 - 0x214];
    void *model;
    u8 pad_234[0x75c - 0x234];
    s32 animId;
    s32 animFrame;
    u8 pad_764[0x9ac - 0x764];
    u64 stateFlags;
    u8 mode;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 velocity;
    u8 pad_9d4[0x10ec - 0x9d4];
    EnemyNotify onReset;
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern const s16 data_02053580[];

extern void ComputeApproachTarget(VecFx32 *out, int mode);
extern int func_ov058_020d895c(void);
extern int GetSceneSlotAngle(int mode);
extern int func_ov001_0206db8c(int index);
extern BOOL IsGroupMemberActive(int groupId, int index);
extern void ResetAnimationTrackState(TrackRequest *request);
extern int func_ov021_020a8cc0(TrackRequest *request, int groupId);
extern void func_ov052_020ceb80(Enemy *enemy, VecFx32 *target);
extern void *GetActorRegistry(void);
extern void Obj_PlaceInWorld(void *world, void *entity, void *position);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void SetActorPaused(Enemy *enemy, int paused);
extern u16 GetLinkedAngleOffset(Enemy *enemy);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);

void UpdateEnemyApproachState(Enemy *enemy)
{
    AiState *ai = &enemy->ai;
    VecFx32 target;
    TrackRequest request;
    VecFx32 velocity;
    VecFx32 approach;
    int angle;
    int index;

    ComputeApproachTarget(&approach, enemy->mode);
    target = approach;
    switch (func_ov058_020d895c()) {
    case 2:
        index = ai->targetIndex;
        if (index != -1 && IsGroupMemberActive(func_ov001_0206db8c(7), index)) {
            return;
        }
        ResetAnimationTrackState(&request);
        request.id = enemy->mode;
        request.flagB = 0;
        request.flagA = 0;
        request.position = target;
        ai->targetIndex = func_ov021_020a8cc0(&request, func_ov001_0206db8c(7));
        enemy->stateFlags &= ~0x40000ULL;
        func_ov052_020ceb80(enemy, &target);
        Obj_PlaceInWorld(GetActorRegistry(), enemy->model, NULL);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animId != 0xe) {
            if (enemy->onEnterState != NULL) {
                enemy->onEnterState(enemy, 0xe, -1);
            }
            return;
        }
        if (enemy->animFrame >= 0x1d000 && enemy->onAnimDone != NULL) {
            enemy->onAnimDone(enemy, 0);
        }
        break;
    case 3:
        func_ov052_020ceb80(enemy, &target);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animFrame >= 0x1d000 && enemy->onAnimDone != NULL) {
            enemy->onAnimDone(enemy, 0);
        }
        index = ai->targetIndex;
        if (index != -1 && !IsGroupMemberActive(func_ov001_0206db8c(7), index)) {
            enemy->stateFlags &= ~0x20000ULL;
            ai->targetIndex = -1;
        }
        break;
    case 4:
    case 5:
        func_ov052_020ceb80(enemy, &target);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animFrame >= 0x34000 && enemy->onAnimDone != NULL) {
            enemy->onAnimDone(enemy, 0x30000);
        }
        break;
    case 7:
        Obj_SetPosition(enemy->model, &target);
        ai->flags &= ~0x100000;
        SetActorPaused(enemy, 0);
        ai->mode = 0;
        ai->timer = 0;
        angle = (u16)(GetLinkedAngleOffset(enemy) + 0x8000) >> 4;
        velocity.x = -data_02053580[angle];
        velocity.y = 0;
        velocity.z = -data_02053580[(0x400 - angle) & 0xfff];
        func_01ffafb4(0x1000, &velocity, &velocity);
        {
            fx32 x = velocity.x;
            fx32 z = velocity.z;
            fx32 y = velocity.y;
            enemy->velocity.x = x;
            enemy->velocity.y = y;
            enemy->velocity.z = z;
        }
        enemy->stateFlags |= 1;
        enemy->stateFlags &= ~0x200000000ULL;
        enemy->stateFlags &= ~0x1000000ULL;
        enemy->onReset(enemy, 4);
        break;
    case 6:
        func_ov052_020ceb80(enemy, &target);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animFrame >= 0x48000) {
            SetActorPaused(enemy, 1);
        }
        break;
    }
}
