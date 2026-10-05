#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline s64 MulTime(s64 time, fx32 value)
{
    return (time * value) >> 12;
}

void ProjectPositionAtTime(s64 time, const VecFx32 *velocity, const VecFx32 *origin, VecFx32 *out)
{
    VecFx32 offset;
    VecFx32 scaled;
    VecFx32 sum;

    scaled.x = (fx32)(MulTime(time, velocity->x) >> 20);
    scaled.y = (fx32)(MulTime(time, velocity->y) >> 20);
    scaled.z = (fx32)(MulTime(time, velocity->z) >> 20);
    offset = scaled;
    VEC_Add(origin, &offset, &sum);
    *out = sum;
}
