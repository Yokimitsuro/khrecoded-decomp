#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void MultAddVecFx32Out(VecFx32 *out, fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    func_01ffa09c(scale, v, add, &result);
    *out = result;
}
