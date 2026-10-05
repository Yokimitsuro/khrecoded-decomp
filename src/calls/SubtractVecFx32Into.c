#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void SubtractVecFx32Into(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9e3c(a, b, &result);
    *dest = result;
}
