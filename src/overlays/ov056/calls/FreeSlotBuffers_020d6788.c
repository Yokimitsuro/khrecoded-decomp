#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x19c];
    void *slotBuffers;
} ShotEntity;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeSlotBuffers_020d6788(ShotEntity *entity)
{
    NNSi_FndFreeFromDefaultHeap(entity->slotBuffers);
}
