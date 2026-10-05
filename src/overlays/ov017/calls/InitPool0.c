#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

typedef struct {
    u8 pad_000[0x1c4];
    void *pool0;
    u8 pad_1c8[0x10];
    s16 pool0Capacity;
    u16 pool0Count;
} PoolManager;

void InitPool0(PoolManager *manager, s32 capacity)
{
    manager->pool0Capacity = (s16)capacity;
    manager->pool0Count = 0;
    manager->pool0 = NNSi_FndAllocFromDefaultHeap(capacity << 2);
}
