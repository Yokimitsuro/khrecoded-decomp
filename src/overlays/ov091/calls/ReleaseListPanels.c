#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
} MenuScene;

extern void Slot_UnlinkAll(void *objManager);
extern void Obj_Release(void *objManager);

void ReleaseListPanels(MenuScene *scene)
{
    void *bottom = scene->screenObjects[1];

    Slot_UnlinkAll(bottom);
    Obj_Release(bottom);
    Slot_UnlinkAll(scene->screenObjects[0]);
    Obj_Release(scene->screenObjects[0]);
}
