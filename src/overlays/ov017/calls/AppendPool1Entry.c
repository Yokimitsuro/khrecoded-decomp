#include "nitro/types.h"

typedef struct Pool1Entry {
    u32 words[5];
} Pool1Entry;

typedef struct PoolManager {
    u8 pad_000[0x1c4];
    int *pool0;
    Pool1Entry *pool1;
    void *pool2;
    void *pool3;
    int *pool4;
    s16 pool0Capacity;
    u16 pool0Count;
    s16 pool1Capacity;
    u16 pool1Count;
} PoolManager;

extern void InitPool1Entry(Pool1Entry *entry, int arg0, int arg1, int arg2, int arg3);

u16 AppendPool1Entry(PoolManager *manager, int arg0, int arg1, int arg2, int arg3)
{
    u16 index = manager->pool1Count++;

    InitPool1Entry(&manager->pool1[index], arg0, arg1, arg2, arg3);
    return manager->pool1Count - 1;
}
