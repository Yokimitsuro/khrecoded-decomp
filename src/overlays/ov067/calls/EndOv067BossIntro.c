#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x9ac];
    u64 flags;
    u8 pad_9b4[0xfc8 - 0x9b4];
    u8 handle[4];
} BossEntity;

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

extern BossEntity *GetBoundedEntryField(int index);
extern BOOL Camera_ReturnFromPathView(void);
extern void ResetObjHandle(void *handle);
extern void RunHudExitCallback(void);
extern void ApplyTimeScaledSpeed(BossEntity *entity, int speed);
extern void ResetGaugeDisplay(void);
extern void SetManagerEnabled(u32 enabled);
extern void StopEntrySounds(SceneOwner *owner, void *obj);

void EndOv067BossIntro(SceneOwner *owner, void *obj)
{
    BossEntity *entity = GetBoundedEntryField(owner->player);

    Camera_ReturnFromPathView();
    ResetObjHandle(entity->handle);
    entity->flags &= ~0x1000000ULL;
    entity->flags &= ~0x20000000ULL;
    RunHudExitCallback();
    ApplyTimeScaledSpeed(entity, 0x1000);
    ResetGaugeDisplay();
    SetManagerEnabled(0);
    StopEntrySounds(owner, obj);
}
