#include "nitro/types.h"

typedef struct SlotOwner {
    u8 pad_000[0x19c];
    int activeSlot;
    u8 pad_1a0[0x1b0 - 0x1a0];
    int slotTimer;
} SlotOwner;

extern void ResetCountsAndSlots(SlotOwner *owner);

void ResetSlotStateAndNotify(SlotOwner *owner)
{
    owner->slotTimer = 0;
    owner->activeSlot = 0;
    ResetCountsAndSlots(owner);
}
