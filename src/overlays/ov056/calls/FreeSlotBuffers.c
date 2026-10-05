#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x190];
    void *slotBuffers;
} ShotEntity;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeSlotBuffers(ShotEntity *entity)
{
    NNSi_FndFreeFromDefaultHeap(entity->slotBuffers);
}
