#include "nitro/types.h"
#include "nitro/fx.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern s32 ComputeOneMinusSquareFraction(void);

/* Combines a dot product with a scaled fraction. */
u32 ScaleDotProductFraction(const VecFx32 *a, s32 scale, const VecFx32 *b) {
    VEC_DotProduct(a, b);
    s32 fraction = ComputeOneMinusSquareFraction();
    s64 product = (s64)fraction * (s64)scale + 0x800;
    return (u32)(product >> 0xc);
}
