#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void ScaleVecFx32InPlace(VecFx32 *vec, s32 sign);

void func_02048b44(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    ScaleVecFx32InPlace(&tmp, sign);
    *out = tmp;
}
