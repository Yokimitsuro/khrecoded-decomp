#include "nitro/types.h"

typedef struct {
    void *slots;
    s8 slotCount;
} EffectPool;

typedef struct {
    u8 pad_000[0x18c];
    EffectPool effectPool;
} EffectOwner;

extern void func_ov056_020d7e54(EffectPool *pool);

void ReleaseEffectPool(EffectOwner *owner)
{
    func_ov056_020d7e54(&owner->effectPool);
}
