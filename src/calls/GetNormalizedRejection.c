#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern fx32 NormalizeIfShort(VecFx32 *vec);
extern VecFx32 GetPerpendicularVector(const VecFx32 *vec);
extern const VecFx32 data_0205344c;

static inline BOOL IsVecNearZero(const VecFx32 *vec, VecFx32 *scratch)
{
    *scratch = *vec;
    return AreVecsWithinRange16(scratch, &data_0205344c);
}

static inline VecFx32 UnitPerpendicular(const VecFx32 *vec)
{
    VecFx32 perpendicular;
    VecFx32 normal;
    perpendicular = GetPerpendicularVector(vec);
    VEC_Normalize(&perpendicular, &normal);
    return normal;
}

static inline VecFx32 NormalizedIfShort(VecFx32 vec)
{
    NormalizeIfShort(&vec);
    return vec;
}

VecFx32 GetNormalizedRejection(const VecFx32 *vec, const VecFx32 *axis, fx32 *outDot)
{
    VecFx32 check;
    VecFx32 diff;
    VecFx32 projected;
    VecFx32 subtrahend;
    VecFx32 rejection;
    fx32 dot = VEC_DotProduct(vec, axis);

    *outDot = dot;
    projected = *axis;
    ScaleVecFx32InPlace(&projected, dot);
    subtrahend = projected;
    VEC_Subtract(vec, &subtrahend, &diff);
    rejection = diff;
    if (IsVecNearZero(&diff, &check)) {
        return UnitPerpendicular(vec);
    }
    return NormalizedIfShort(rejection);
}
