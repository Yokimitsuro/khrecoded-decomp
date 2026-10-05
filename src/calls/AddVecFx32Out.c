#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void AddVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9e0c(a, b, &result);
    *out = result;
}
