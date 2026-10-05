#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c4];
    u8 *pool0;
} PoolManager;

typedef struct {
    u8 pad_00[4];
    PoolManager *manager;
} PoolOwner;

u8 *GetPool0Entry(PoolOwner *owner, int index)
{
    return owner->manager->pool0 + index * 4;
}
