#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 ComputeOneMinusSquareFraction(fx32 value);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

fx32 BlendVectorsBySqrtComplement(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out)
{
    fx32 sqrtComplement = ComputeOneMinusSquareFraction(t);
    VecFx32 scaled = *a;
    ScaleVecFx32InPlace(&scaled, t);
    *out = scaled;
    func_01ffa09c(sqrtComplement * factor, b, out, out);
    return sqrtComplement;
}
