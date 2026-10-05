#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x200];
    u8 objManagers[2][0x6434];
} SceneWork;

extern void Slot_UnlinkAll(void *manager);
extern int Obj_Release(void *manager);

void ReleaseSceneObjManagers(SceneWork *work)
{
    void *second = work->objManagers[1];
    Slot_UnlinkAll(second);
    Obj_Release(second);
    Slot_UnlinkAll(work->objManagers[0]);
    Obj_Release(work->objManagers[0]);
}
