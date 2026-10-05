#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CachedBounds {
    VecFx32 min;
    VecFx32 max;
    u8 pad_18[0x14];
    u8 frameStamp;
} CachedBounds;

typedef struct Bounds {
    VecFx32 min;
    VecFx32 max;
} Bounds;

extern u8 data_02060780;

BOOL CachedBounds_NeedsRefresh(CachedBounds *cached, const Bounds *query)
{
    if (cached->frameStamp != data_02060780) {
        cached->frameStamp = data_02060780;
        return TRUE;
    }
    if (query->min.x > cached->min.x || query->max.x < cached->max.x ||
        query->min.y > cached->min.y || query->max.y < cached->max.y ||
        query->min.z > cached->min.z || query->max.z < cached->max.z) {
        return TRUE;
    }
    return FALSE;
}
