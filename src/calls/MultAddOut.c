#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void MultAddOut(VecFx32 *dst, fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 tmp;
    VEC_MultAdd(scale, v, add, &tmp);
    *dst = tmp;
}
