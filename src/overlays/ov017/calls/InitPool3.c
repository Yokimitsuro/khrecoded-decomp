#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

typedef struct {
    u8 pad_000[0x1d0];
    void *pool3;
    u8 pad_1d4[0x10];
    s16 pool3Capacity;
    u16 pool3Count;
} PoolManager;

void InitPool3(PoolManager *manager, s32 capacity)
{
    manager->pool3Capacity = (s16)capacity;
    manager->pool3Count = 0;
    manager->pool3 = NNSi_FndAllocFromDefaultHeap(capacity * 0xc);
}
