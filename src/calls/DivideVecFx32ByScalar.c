#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s32 _s32_div_f(s32 numerator, s32 denominator);

void DivideVecFx32ByScalar(VecFx32 *vec, s32 divisor)
{
    vec->x = _s32_div_f(vec->x, divisor);
    vec->y = _s32_div_f(vec->y, divisor);
    vec->z = _s32_div_f(vec->z, divisor);
}
