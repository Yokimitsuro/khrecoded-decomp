#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c8];
    u8 *pool1;
} PoolManager;

typedef struct {
    u8 pad_00[4];
    PoolManager *manager;
} PoolOwner;

u8 *GetPool1Entry(PoolOwner *owner, int index)
{
    return owner->manager->pool1 + index * 0x14;
}
