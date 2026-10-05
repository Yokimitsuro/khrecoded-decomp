#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

fx32 NormalizeOrVerticalAxis(const VecFx32 *src, VecFx32 *dst, BOOL vertical)
{
    VecFx32 axis;
    fx32 y;

    if (!vertical) {
        return func_01ffaff4(src, dst);
    }
    y = src->y;
    SetVec(&axis, 0, y >= 0 ? 0x1000 : -0x1000, 0);
    *dst = axis;
    return y;
}
