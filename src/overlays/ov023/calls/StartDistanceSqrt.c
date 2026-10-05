#include "nitro/types.h"
#include "nitro/fx_types.h"

static inline void SetSqrt64(u64 param)
{
    *(vu16 *)0x040002b0 = 1;
    *(vu64 *)0x040002b8 = param;
}

void StartDistanceSqrt(const VecFx32 *a, const VecFx32 *b)
{
    s64 dx = a->x - b->x;
    s64 dy;
    s64 distSq;

    distSq = dx * dx;
    dy = a->y - b->y;
    distSq += dy * dy;
    SetSqrt64((u64)(distSq << 2));
}
