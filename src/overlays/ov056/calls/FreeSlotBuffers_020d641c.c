#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    void *slotBuffers;
} ShotEntity;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeSlotBuffers_020d641c(ShotEntity *entity)
{
    NNSi_FndFreeFromDefaultHeap(entity->slotBuffers);
}
