#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x9ac];
    u64 flags;
} BossEntity;

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    u8 pad_00[0x4c];
    s16 emitter;
    u8 pad_4e[0x33];
    s8 soundHandle;
} SceneObject;

extern BossEntity *GetBoundedEntryField(int index);
extern BOOL Camera_ReturnFromPathView(void);
extern void RunHudExitCallback(void);
extern void StopAndClearSoundEmitter(int emitter, int handle);
extern void ResetGaugeDisplay(void);
extern void SetManagerEnabled(u32 enabled);
extern void StopEntrySounds(SceneOwner *owner, SceneObject *obj);

void EndOv068BossIntro(SceneOwner *owner, SceneObject *obj)
{
    BossEntity *entity = GetBoundedEntryField(owner->player);
    int handle;
    int emitter;

    Camera_ReturnFromPathView();
    entity->flags &= ~0x1000000ULL;
    entity->flags &= ~0x20000000ULL;
    RunHudExitCallback();
    emitter = obj->emitter;
    handle = obj->soundHandle;
    if (handle != -1) {
        StopAndClearSoundEmitter(emitter, handle);
        obj->soundHandle = -1;
    }
    ResetGaugeDisplay();
    SetManagerEnabled(0);
    StopEntrySounds(owner, obj);
}
