#include "nitro/types.h"

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
    void *handler;
    s32 state;
} EnemyStateSlot;

struct Enemy {
    u8 pad_000[0x1f8];
    EnemyCallback onEnterState;
    u8 pad_1fc[0x230 - 0x1fc];
    void *model;
    u8 pad_234[0x9ac - 0x234];
    u64 stateFlags;
    u8 pad_9b4[0x9bc - 0x9b4];
    EnemyStateSlot stateSlot;
    u8 pad_9c4[0x10ec - 0x9c4];
    EnemyNotify onReset;
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern void *GetActorRegistry(void);
extern void Obj_PlaceInWorld(void *world, void *entity, void *position);

void ResetEnemyLaunchState(Enemy *enemy)
{
    AiState *ai = &enemy->ai;
    EnemyStateSlot *slot = &enemy->stateSlot;

    if ((enemy->stateFlags & 0x20000) == 0 && slot->state != 0x1e) {
        return;
    }
    ai->targetIndex = -1;
    ai->timer = 0;
    enemy->stateFlags &= ~0x20000ULL;
    enemy->stateFlags &= ~0x40000ULL;
    Obj_PlaceInWorld(GetActorRegistry(), enemy->model, NULL);
    enemy->onReset(enemy, 1);
    if (enemy->onEnterState != NULL) {
        enemy->onEnterState(enemy, 0, -1);
    }
}
