#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32ComponentsConditional(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 func_0204bad8(const VecFx32 *source, s32 skipHorizontal);
extern const VecFx32 data_0205344c;

static inline void SubtractVecConditional(VecFx32 *vec, const VecFx32 *offset, s32 skipHorizontal)
{
    if (skipHorizontal == 0) {
        vec->x -= offset->x;
        vec->z -= offset->z;
    }
    vec->y -= offset->y;
}

VecFx32 GetNormalizedAxisRejectionMasked(const VecFx32 *vec, const VecFx32 *axis, s32 skipHorizontal)
{
    VecFx32 check;
    VecFx32 fallback;
    VecFx32 rejection;
    VecFx32 projected;
    VecFx32 offset;
    VecFx32 result;
    VecFx32 *offsetPtr;
    fx32 dot = VEC_DotProduct(vec, axis);

    projected = *axis;
    ScaleVecFx32ComponentsConditional(&projected, dot, skipHorizontal);
    offsetPtr = &offset;
    *offsetPtr = projected;
    rejection = *vec;
    SubtractVecConditional(&rejection, offsetPtr, skipHorizontal);
    check = rejection;
    if (AreVecsWithinRange16(&check, &data_0205344c)) {
        fallback = func_0204bad8(vec, skipHorizontal);
        return fallback;
    }
    VEC_Normalize(&check, &result);
    return result;
}
