#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VecFx32ScaledCopy(VecFx32 *out, const VecFx32 *v, fx32 scale);
extern void SubtractVecFx32Into(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

void ComputeVectorRejection(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    fx32 dot = VEC_DotProduct(a, b);
    VecFx32 result;
    VecFx32 scaled;

    VecFx32ScaledCopy(&scaled, b, dot);
    SubtractVecFx32Into(&result, a, &scaled);
    *out = result;
}
