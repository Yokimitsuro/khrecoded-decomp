#include "nitro/types.h"

typedef struct ResourceSlot {
    u8 pad00[0x90];
} ResourceSlot;

typedef struct ResourceOwner {
    u8 pad00[0x44];
    void *buffer;
    u8 pad48[0x6c - 0x48];
    ResourceSlot *slots;
    s32 slotCount;
} ResourceOwner;

extern void func_ov021_020aa918(ResourceSlot *slot, int mode);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

void FreeResourceSlots(ResourceOwner *owner, int mode)
{
    int i;

    for (i = 0; i < owner->slotCount; i++) {
        func_ov021_020aa918(&owner->slots[i], mode);
    }
    NNSi_FndFreeFromDefaultHeap(owner->buffer);
    NNSi_FndFreeFromDefaultHeap(owner->slots);
}
