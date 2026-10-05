#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ExitFunc)(Actor *actor, int arg, int value);
typedef void (*InitFunc)(Actor *actor);
typedef void (*SetModeFunc)(Actor *actor, int mode);

typedef struct {
    u8 data[0x230];
} SlotTable;

struct Actor {
    u8 pad_0000[0x1f8];
    ExitFunc onModeExit;
    u8 pad_01fc[0x6ac - 0x1fc];
    VecFx32 knockback;
    u8 pad_06b8[0x75c - 0x6b8];
    int mode;
    u8 pad_0760[0x9b4 - 0x760];
    u8 player;
    u8 pad_09b5[3];
    int kind;
    u8 pad_09bc[4];
    int stageType;
    u8 pad_09c4[4];
    VecFx32 velocity;
    VecFx32 impulse;
    VecFx32 drift;
    u8 pad_09ec[4];
    fx32 timeScale;
    u8 pad_09f4[4];
    int airTime;
    u8 pad_09fc[0xa10 - 0x9fc];
    u8 speed[0xb18 - 0xa10];
    int hitCount;
    u8 pad_0b1c[0xb2c - 0xb1c];
    u8 stats[0xb68 - 0xb2c];
    SlotTable slotTables[2];
    u8 handle[0x1034 - 0xfc8];
    s8 targetSlot;
    u8 targetLock;
    s8 targetPrev;
    u8 palette;
    u8 pad_1038[0x105c - 0x1038];
    u8 linkState[0x1070 - 0x105c];
    u8 members[0x10d4 - 0x1070];
    u8 stepTimer[8];
    u8 idleTimer[0x10e8 - 0x10dc];
    InitFunc onInit;
    SetModeFunc setMode;
    u8 pad_10f0[0x1100 - 0x10f0];
    s16 markerIndex;
    u8 pad_1102[2];
    int lockTarget;
    u8 marker[4];
};

extern void func_ov052_020c7480(Actor *actor);
extern void ApplyTimeScaledSpeed(Actor *actor, fx32 targetSpeed);
extern s32 GetClampedPaletteSlot(void);
extern BOOL IsFieldFlag16Set(void);
extern void ResetMotionState_020c9fa8(void *speed);
extern void func_ov052_020ccab0(void *timer, int duration);
extern void ClearRecord68(void *handle);
extern void InitSlotTable(SlotTable *table, u8 player);
extern void InitSlotMarker(void *marker, u32 player);
extern void func_ov021_020ad5e8(void *members);
extern void func_ov021_020a7ce8(void *stats, int kind, u8 player);
extern void LoadSlotModels(Actor *actor, void *linkState);

void ResetActorCombatState(Actor *actor)
{
    int i;

    func_ov052_020c7480(actor);
    actor->velocity.z = 0;
    actor->velocity.y = 0;
    actor->velocity.x = 0;
    actor->impulse.z = 0;
    actor->impulse.y = 0;
    actor->impulse.x = 0;
    actor->drift.z = 0;
    actor->drift.y = 0;
    actor->drift.x = 0;
    actor->knockback.z = 0;
    actor->knockback.y = 0;
    actor->knockback.x = 0;
    actor->timeScale = 0x1000;
    ApplyTimeScaledSpeed(actor, 0x1000);
    actor->stageType = 0;
    actor->airTime = 0;
    actor->lockTarget = -1;
    actor->targetSlot = -1;
    actor->targetPrev = -1;
    actor->targetLock = 0;
    actor->palette = GetClampedPaletteSlot();
    if (IsFieldFlag16Set()) {
        actor->palette = 4;
    }
    ResetMotionState_020c9fa8(actor->speed);
    actor->hitCount = 0;
    func_ov052_020ccab0(actor->stepTimer, 1);
    func_ov052_020ccab0(actor->idleTimer, 0x69);
    ClearRecord68(actor->handle);
    for (i = 0; i < 2; i++) {
        InitSlotTable(&actor->slotTables[i], actor->player);
    }
    InitSlotMarker(actor->marker, actor->player);
    func_ov021_020ad5e8(actor->members);
    func_ov021_020a7ce8(actor->stats, actor->kind, actor->player);
    actor->markerIndex = -1;
    LoadSlotModels(actor, actor->linkState);
    if (actor->onInit != NULL) {
        actor->onInit(actor);
    }
    actor->setMode(actor, 1);
    if (actor->mode == -1 && actor->onModeExit != NULL) {
        actor->onModeExit(actor, 0, -1);
    }
}
