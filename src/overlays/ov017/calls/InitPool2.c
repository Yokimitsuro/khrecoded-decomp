#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

typedef struct {
    u8 pad_000[0x1cc];
    void *pool2;
    u8 pad_1d0[0x10];
    s16 pool2Capacity;
    u16 pool2Count;
} PoolManager;

void InitPool2(PoolManager *manager, s32 capacity)
{
    manager->pool2Capacity = (s16)capacity;
    manager->pool2Count = 0;
    manager->pool2 = NNSi_FndAllocFromDefaultHeap(capacity * 0x28);
}
