#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *vec);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);
extern void DivideVecByLength(VecFx32 *vec, fx32 length);
extern VecFx32 GetPerpendicularVector(const VecFx32 *vec);

static inline fx32 VecLength(const VecFx32 *vec, VecFx32 *scratch)
{
    *scratch = *vec;
    return VEC_Mag(scratch);
}

static inline VecFx32 UnitPerpendicular(const VecFx32 *vec)
{
    VecFx32 perpendicular;
    VecFx32 normal;
    perpendicular = GetPerpendicularVector(vec);
    VEC_Normalize(&perpendicular, &normal);
    return normal;
}

static inline VecFx32 DividedByLength(VecFx32 vec, fx32 length)
{
    DivideVecByLength(&vec, length);
    return vec;
}

VecFx32 GetUnitCrossReportDegenerate(const VecFx32 *vec, const VecFx32 *axis, BOOL *degenerate)
{
    VecFx32 check;
    VecFx32 copy;
    VecFx32 cross;
    fx32 length;

    VEC_CrossProduct(vec, axis, &cross);
    copy = cross;
    length = VecLength(&cross, &check);
    *degenerate = length < 0x10;
    if (*degenerate) {
        return UnitPerpendicular(vec);
    }
    return DividedByLength(copy, length);
}

