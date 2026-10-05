#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x198];
    void *slotBuffers;
} ShotEntity;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeSlotBuffers_020d7060(ShotEntity *entity)
{
    NNSi_FndFreeFromDefaultHeap(entity->slotBuffers);
}
