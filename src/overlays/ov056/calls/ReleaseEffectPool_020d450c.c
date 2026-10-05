#include "nitro/types.h"

typedef struct {
    void *slots;
    s8 slotCount;
} EffectPool;

typedef struct {
    u8 pad_000[0x18c];
    EffectPool effectPool;
} EffectOwner;

extern void FreeModelSlots(EffectPool *pool);

void ReleaseEffectPool_020d450c(EffectOwner *owner)
{
    FreeModelSlots(&owner->effectPool);
}
