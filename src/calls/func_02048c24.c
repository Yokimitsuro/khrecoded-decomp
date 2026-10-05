#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void DivideVecByLength(VecFx32 *vec, s32 sign);

void func_02048c24(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    DivideVecByLength(&tmp, sign);
    *out = tmp;
}
