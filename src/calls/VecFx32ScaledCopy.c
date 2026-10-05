#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

VecFx32 VecFx32ScaledCopy(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;
    ScaleVecFx32InPlace(&result, scale);
    return result;
}
