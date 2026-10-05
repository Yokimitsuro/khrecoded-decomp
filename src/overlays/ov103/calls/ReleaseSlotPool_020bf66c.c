#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x174];
    u8 slotPool[1];
} MenuScene;

extern void Slot_UnlinkAll(void *pool);
extern int Obj_Release(void *object);

void ReleaseSlotPool_020bf66c(MenuScene *scene)
{
    Slot_UnlinkAll(scene->slotPool);
    Obj_Release(scene->slotPool);
}
