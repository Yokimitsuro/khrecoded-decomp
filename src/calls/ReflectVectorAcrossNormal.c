#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

static inline VecFx32 Subtract(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 RemoveProjection(const VecFx32 *vec, const VecFx32 *normal)
{
    VecFx32 projected;
    VecFx32 scaled;
    VecFx32 diff;
    fx32 dot = VEC_DotProduct(vec, normal);

    scaled = *normal;
    ScaleVecFx32InPlace(&scaled, dot);
    projected = scaled;
    func_01ff9e3c(vec, &projected, &diff);
    return diff;
}

VecFx32 ReflectVectorAcrossNormal(const VecFx32 *vec, const VecFx32 *normal)
{
    VecFx32 offset = RemoveProjection(vec, normal);

    offset.x <<= 1;
    offset.y <<= 1;
    offset.z <<= 1;
    return Subtract(vec, &offset);
}
