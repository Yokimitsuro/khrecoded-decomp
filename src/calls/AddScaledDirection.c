#include "nitro/types.h"
#include "nitro/fx_types.h"

void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

VecFx32 AddScaledDirection(fx32 scale, const VecFx32 *direction, const VecFx32 *origin, BOOL verticalOnly)
{
    if (!verticalOnly) {
        VecFx32 result;
        VEC_MultAdd(scale, direction, origin, &result);
        return result;
    } else {
        /* Only the vertical component is applied */
        VecFx32 result;
        result.x = origin->x;
        result.y = origin->y + (fx32)(((s64)direction->y * scale + 0x800) >> 12);
        result.z = origin->z;
        return result;
    }
}
