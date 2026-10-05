#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32(VecFx32 *vec);

fx32 FlipVectorIfDotNegative(VecFx32 *a, const VecFx32 *b)
{
    fx32 dot = VEC_DotProduct(a, b);
    if (dot < 0) {
        NegateVecFx32(a);
    }
    return dot;
}
