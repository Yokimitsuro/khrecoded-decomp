#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void ApplyScalarToVec3(VecFx32 *vec, s32 sign);

void func_0204966c(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    ApplyScalarToVec3(&tmp, sign);
    *out = tmp;
}
