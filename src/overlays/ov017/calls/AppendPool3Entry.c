#include "nitro/types.h"

typedef struct PoolTriple {
    u32 words[3];
} PoolTriple;

typedef struct PoolManager {
    u8 pad_000[0x1c4];
    int *pool0;
    void *pool1;
    void *pool2;
    PoolTriple *pool3;
    int *pool4;
    s16 pool0Capacity;
    u16 pool0Count;
    s16 pool1Capacity;
    u16 pool1Count;
    s16 pool2Capacity;
    u16 pool2Count;
    s16 pool3Capacity;
    u16 pool3Count;
} PoolManager;

extern void CopyTriple(PoolTriple *dest, PoolTriple *src);

u16 AppendPool3Entry(PoolManager *manager, PoolTriple *entry)
{
    u16 index = manager->pool3Count++;

    CopyTriple(&manager->pool3[index], entry);
    return manager->pool3Count - 1;
}
