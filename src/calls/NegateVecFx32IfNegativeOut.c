#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32IfNegative(VecFx32 *vec, s32 sign);

void NegateVecFx32IfNegativeOut(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    NegateVecFx32IfNegative(&tmp, sign);
    *out = tmp;
}
