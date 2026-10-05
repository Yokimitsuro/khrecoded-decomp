#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void MultAddOut(VecFx32 *dst, fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 tmp;
    func_01ffa09c(scale, v, add, &tmp);
    *dst = tmp;
}
