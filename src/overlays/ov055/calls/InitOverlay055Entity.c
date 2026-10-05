#include "nitro/types.h"

typedef void (*EntityCallback)(void);

typedef struct Entity {
    u8 pad_000[0x1ec];
    EntityCallback drawCallback;
    u8 pad_1f0[0x1f8 - 0x1f0];
    EntityCallback eventCallback;
    u8 pad_1fc[0x200 - 0x1fc];
    EntityCallback resetCallback;
    u8 pad_204[0x20c - 0x204];
    EntityCallback modeCallback;
    u8 pad_210[0x218 - 0x210];
    EntityCallback stepCallback;
    EntityCallback flagsCallback;
    u8 pad_220[0x6bc - 0x220];
    s32 targets[4];
    u8 pad_6cc[0x9ac - 0x6cc];
    u64 stateFlags;
    u8 kind;
    u8 pad_9b5[3];
    s32 unk_9b8;
    u8 pad_9bc[0x10e8 - 0x9bc];
    EntityCallback actionCallback;
    EntityCallback stateCallback;
    EntityCallback thinkCallback;
    u8 pad_10f4[0x1258 - 0x10f4];
    u8 work[4];
} Entity;

extern void InitTrackedRecordEntry(void *work);
extern void InstallActorCallbacks(Entity *entity);
extern void HandleEnemyEvent(void);
extern void SetEnemyModeEnabled(void);
extern void LoadSceneSoundArchives(void);
extern void UpdateEnemyAnimation(void);
extern void FilterEnemyStatusFlags(void);
extern void SetEnemyPose(void);
extern void ChangeEnemyState(void);
extern void SetupOverlay055Entity(void);
extern void UpdateEnemyFallCheck(void);

void InitOverlay055Entity(Entity *entity, u8 kind)
{
    int i;

    InitTrackedRecordEntry(entity->work);
    entity->kind = kind;
    entity->unk_9b8 = 1;
    entity->stateFlags = 0;
    entity->stateFlags |= 0x400;
    for (i = 0; i < 4; i++) {
        entity->targets[i] = -1;
    }
    entity->targets[1] = -2;
    InstallActorCallbacks(entity);
    entity->eventCallback = HandleEnemyEvent;
    entity->modeCallback = SetEnemyModeEnabled;
    entity->stepCallback = LoadSceneSoundArchives;
    entity->drawCallback = UpdateEnemyAnimation;
    entity->flagsCallback = FilterEnemyStatusFlags;
    entity->resetCallback = SetEnemyPose;
    entity->stateCallback = ChangeEnemyState;
    entity->actionCallback = SetupOverlay055Entity;
    entity->thinkCallback = UpdateEnemyFallCheck;
}
