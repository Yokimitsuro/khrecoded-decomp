#include "nitro/types.h"
#include "nitro/fx_types.h"

void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void GetPointAlongDirectionQ27(s32 t, const VecFx32 *direction, const VecFx32 *origin, VecFx32 *out)
{
    VecFx32 offset;
    VecFx32 scaled;
    VecFx32 sum;

    /* Scale factor uses 27 fractional bits */
    scaled.x = (fx32)(((s64)direction->x * t) >> 27);
    scaled.y = (fx32)(((s64)direction->y * t) >> 27);
    scaled.z = (fx32)(((s64)direction->z * t) >> 27);
    offset = scaled;
    func_01ff9e0c(origin, &offset, &sum);
    *out = sum;
}
