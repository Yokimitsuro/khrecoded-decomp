#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void ComputeCrossProduct(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9ea8(a, b, &result);
    *out = result;
}
