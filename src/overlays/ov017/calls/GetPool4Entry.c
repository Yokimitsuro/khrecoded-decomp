#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1d4];
    u8 *pool4;
} PoolManager;

typedef struct {
    u8 pad_00[4];
    PoolManager *manager;
} PoolOwner;

u8 *GetPool4Entry(PoolOwner *owner, int index)
{
    return owner->manager->pool4 + index * 4;
}
