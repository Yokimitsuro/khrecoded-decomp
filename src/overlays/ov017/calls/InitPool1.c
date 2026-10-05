#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

typedef struct {
    u8 pad_000[0x1c8];
    void *pool1;
    u8 pad_1cc[0x10];
    s16 pool1Capacity;
    u16 pool1Count;
} PoolManager;

void InitPool1(PoolManager *manager, s32 capacity)
{
    manager->pool1Capacity = (s16)capacity;
    manager->pool1Count = 0;
    manager->pool1 = NNSi_FndAllocFromDefaultHeap(capacity * 0x14);
}
