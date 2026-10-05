#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_0205344c;
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern fx32 NormalizeIfShort(VecFx32 *vec);
extern VecFx32 GetPerpendicularVector(const VecFx32 *vec);

static inline BOOL IsNearZero(const VecFx32 *vec, VecFx32 *scratch)
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

VecFx32 GetUnitRejectionFromAxis(const VecFx32 *vec, const VecFx32 *axis)
{
    VecFx32 check;
    VecFx32 rejected;
    VecFx32 scaled;
    VecFx32 projection;
    VecFx32 copy;
    fx32 dot;

    dot = VEC_DotProduct(vec, axis);
    scaled = *axis;
    ScaleVecFx32InPlace(&scaled, dot);
    projection = scaled;
    func_01ff9e3c(vec, &projection, &rejected);
    copy = rejected;
    if (IsNearZero(&rejected, &check)) {
        return UnitPerpendicular(vec);
    }
    return NormalizedIfShort(copy);
}

