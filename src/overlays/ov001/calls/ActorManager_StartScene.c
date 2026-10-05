#include "nitro/types.h"

typedef struct SceneRequest {
    char name[0x10];
    u32 param;
} SceneRequest;

typedef struct ActorManager {
    u8 pad_000[0x3ee4];
    void *rootObject;
    u8 pad_3ee8[4];
    char resourceName[0x14];
    s32 field_3f00;
    s32 field_3f04;
    s32 slots[5];
    u32 field_3f1c;
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern void ReloadModeMessageArchive(void);
extern void TryFinishIntroSequence(void);
extern void *Obj_SetWord14(void *object, void (*callback)(void));

void ActorManager_StartScene(SceneRequest *request)
{
    ActorManager *manager = data_ov001_020a0500;
    int slotIndex;

    manager->field_3f1c = request->param;
    OS_SPrintf(manager->resourceName, request->name);
    manager->field_3f00 = -1;
    manager->field_3f04 = 0x1f;
    for (slotIndex = 0; slotIndex < 5; slotIndex++) {
        manager->slots[slotIndex] = -1;
    }
    ReloadModeMessageArchive();
    Obj_SetWord14(manager->rootObject, TryFinishIntroSequence);
}
