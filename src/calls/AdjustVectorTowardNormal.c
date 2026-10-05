#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void AdjustVectorTowardNormal(VecFx32 *a, const VecFx32 *b, fx32 factor)
{
    fx32 dot = VEC_DotProduct(a, b);
    if (dot < 0) {
        s64 product = (s64)dot * factor + 0x800;
        func_01ffa09c(-(dot + (fx32)(product >> 0xc)), b, a, a);
    }
}
