#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x180];
    u8 slotPool[1];
} SlotPoolOwner;

extern void NNS_FndInitListWithOffset0_0204f130(void *list);

void InitSlotPool(SlotPoolOwner *owner)
{
    NNS_FndInitListWithOffset0_0204f130(owner->slotPool);
}
