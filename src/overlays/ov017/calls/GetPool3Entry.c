#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1d0];
    u8 *pool3;
} PoolManager;

typedef struct {
    u8 pad_00[4];
    PoolManager *manager;
} PoolOwner;

u8 *GetPool3Entry(PoolOwner *owner, int index)
{
    return owner->manager->pool3 + index * 0xc;
}
