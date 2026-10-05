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
    u8 pad_00[0x3c];
    int nextState;
    u8 pad_40[0x44];
    u8 cameraPath[0x70];
    int introActive;
} SceneObject;

extern BossEntity *GetBoundedEntryField(int index);
extern void RunHudEnterCallback(void);
extern void CameraPath_Start(void *path);
extern void ApplyTimeScaledSpeed(BossEntity *entity, int speed);

int StartOv067BossIntro(SceneOwner *owner, SceneObject *obj, int *wait)
{
    BossEntity *entity = GetBoundedEntryField(owner->player);

    obj->introActive = 1;
    entity->flags |= 0x1000000;
    entity->flags |= 0x20000000;
    RunHudEnterCallback();
    CameraPath_Start(obj->cameraPath);
    ApplyTimeScaledSpeed(entity, 0x1666);
    entity->flags |= 0x40;
    *wait = 0x18;
    return obj->nextState;
}
