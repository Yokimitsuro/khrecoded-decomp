#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s16 data_02053580[];

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *v, fx32 scale);
extern void PickPerpendicularAxis(VecFx32 *out, const VecFx32 *v);
extern void GetUnitCross(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800LL) >> 12);
}

static inline VecFx32 CrossVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct(a, b, &result);
    return result;
}

static inline VecFx32 OrthogonalVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    GetUnitCross(&result, a, b);
    return result;
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_MultAdd(scale, a, b, &result);
    return result;
}

void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *target, fx32 angle)
{
    VecFx32 axis;
    fx32 length;
    int index;

    if (angle == 0) {
        return;
    }
    axis = CrossVec(vec, target);
    if (axis.x == 0 && axis.y == 0 && axis.z == 0) {
        VecFx32 perpendicular;
        if (VEC_DotProduct(vec, target) >= 0) {
            return;
        }
        PickPerpendicularAxis(&perpendicular, target);
        axis = CrossVec(vec, &perpendicular);
    }
    axis = OrthogonalVec(&axis, vec);
    length = VEC_Mag(vec);
    index = (int)((((s64)angle << 16) / 0x6488) & 0xffff) >> 4;
    ScaleVecFx32InPlace(vec, data_02053580[(0x400 - index) & 0xfff]);
    *vec = MultAddVec(FxMul(data_02053580[index], length), &axis, vec);
}
