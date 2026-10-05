#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern VecFx32 GetUnitCross(const VecFx32 *a, const VecFx32 *b);
extern void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *axis, s32 angle);

static inline VecFx32 RemoveProjection(const VecFx32 *vec, const VecFx32 *normal, fx32 dot)
{
    VecFx32 projected;
    VecFx32 scaled;
    VecFx32 diff;

    scaled = *normal;
    ScaleVecFx32InPlace(&scaled, dot);
    projected = scaled;
    VEC_Subtract(vec, &projected, &diff);
    return diff;
}

static inline VecFx32 MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd(scale, v, add, &result);
    return result;
}

static inline VecFx32 Perpendicular(const VecFx32 *a, const VecFx32 *b)
{
    return GetUnitCross(a, b);
}

void RotateVectorAroundAxis(VecFx32 *vec, const VecFx32 *axis, s32 angle)
{
    fx32 dot = VEC_DotProduct(vec, axis);
    VecFx32 offset = RemoveProjection(vec, axis, dot);
    VecFx32 perpendicular;

    perpendicular = Perpendicular(vec, axis);
    RotateVecTowardVec(&offset, &perpendicular, angle);
    *vec = MultAdd(dot, axis, &offset);
}
