#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1cc];
    u8 *pool2;
} PoolManager;

typedef struct {
    u8 pad_00[4];
    PoolManager *manager;
} PoolOwner;

u8 *GetPool2Entry(PoolOwner *owner, int index)
{
    return owner->manager->pool2 + index * 0x28;
}
