#include "nitro/types.h"

typedef struct SlotOwner {
    u8 pad_000[0x198];
    void *slotBuffer;
} SlotOwner;

extern void UpdateSceneGroupEntries(SlotOwner *owner, void *buffer);

void StoreSlotBufferAndInit(SlotOwner *owner, void *buffer)
{
    owner->slotBuffer = buffer;
    UpdateSceneGroupEntries(owner, buffer);
}
