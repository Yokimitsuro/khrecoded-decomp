#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} ObjManager;

typedef struct {
    u8 pad_000[0x45c];
    ObjManager objManagers[2];
} SceneWork;

extern void Slot_UnlinkAll(void *manager);
extern int Obj_Release(void *manager);

void ReleaseObjManagers(SceneWork *work)
{
    ObjManager *manager;

    manager = &work->objManagers[1];
    Slot_UnlinkAll(manager);
    Obj_Release(manager);
    manager = &work->objManagers[0];
    Slot_UnlinkAll(manager);
    Obj_Release(manager);
}
