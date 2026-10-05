#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x180];
    u8 slotPool[1];
} SlotPoolOwner;

extern void Slot_UnlinkAll(void *pool);
extern int Obj_Release(void *object);

void ReleaseSlotPool(SlotPoolOwner *owner)
{
    Slot_UnlinkAll(owner->slotPool);
    Obj_Release(owner->slotPool);
}
