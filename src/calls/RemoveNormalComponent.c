#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_02048b44(VecFx32 *out, const VecFx32 *v, fx32 scale);
extern void SubtractVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

void RemoveNormalComponent(VecFx32 *out, const VecFx32 *vec, const VecFx32 *normal, fx32 *outDot)
{
    VecFx32 result;
    VecFx32 projected;
    fx32 dot = VEC_DotProduct(vec, normal);

    *outDot = dot;
    func_02048b44(&projected, normal, dot);
    SubtractVecFx32Out(&result, vec, &projected);
    *out = result;
}
