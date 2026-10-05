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

extern void func_ov017_020a4fa0(int *p, int v);

u16 AppendPool0Value(PoolManager *manager, int value)
{
    u16 index = manager->pool0Count++;

    func_ov017_020a4fa0(&manager->pool0[index], value);
    return manager->pool0Count - 1;
}
