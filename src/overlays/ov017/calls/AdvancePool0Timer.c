#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PoolOwner {
    u8 pad_00[0x4c];
    fx32 pendingTime;
} PoolOwner;

extern fx32 *GetPool0Entry(PoolOwner *owner, int index);

BOOL AdvancePool0Timer(fx32 *timer, PoolOwner *owner, int index)
{
    fx32 *limit = GetPool0Entry(owner, index);

    if (*limit == 0) {
        return FALSE;
    }
    *timer += owner->pendingTime + 0x1000;
    owner->pendingTime = 0;
    return *timer >= *limit;
}
