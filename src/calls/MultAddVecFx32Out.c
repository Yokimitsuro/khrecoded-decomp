#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void MultAddVecFx32Out(VecFx32 *out, fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd(scale, v, add, &result);
    *out = result;
}
