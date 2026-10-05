#include "nitro/types.h"

typedef struct BossEntity BossEntity;

struct BossEntity {
    u8 pad_000[0x204];
    void (*onSignal)(BossEntity *entity, int signal);
};

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    int active;
    u8 pad_04[4];
    int handle;
    u8 pad_0c[0x18];
} EffectSlot;

typedef struct {
    u8 pad_00[0x40];
    u8 running;
    u8 pad_41[0xf];
    s16 loopEmitter;
    s16 slotEmitter;
    u8 pad_54[4];
    int loopHandle;
    u8 pad_5c[4];
    EffectSlot slots[10];
} SceneObject;

extern BossEntity *GetBoundedEntryField(int index);
extern void StopAndClearSoundEmitter(int emitter, int handle);
extern void Camera_ChangeModeFromCurrentView(int mode);

void StopOv070BossEffects(SceneOwner *owner, SceneObject *obj)
{
    BossEntity *entity = GetBoundedEntryField(owner->player);
    int i;

    obj->running = 0;
    if (obj->loopHandle >= 0) {
        StopAndClearSoundEmitter(obj->loopEmitter, obj->loopHandle);
        obj->loopHandle = -1;
    }
    for (i = 0; i < 10; i++) {
        EffectSlot *slot = &obj->slots[i];
        if (slot->active) {
            slot->active = 0;
            StopAndClearSoundEmitter(obj->slotEmitter, slot->handle);
            slot->handle = -1;
        }
    }
    if (entity->onSignal != NULL) {
        entity->onSignal(entity, 0x1f);
    }
    Camera_ChangeModeFromCurrentView(0);
}
