#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 FX_DivFx64c(fx32 numer, fx32 denom);

void DivideVecByLength(VecFx32 *vec, fx32 length)
{
    s64 inverse = FX_DivFx64c(0x1000, length);

    vec->x = (fx32)((vec->x * inverse) >> 32);
    vec->y = (fx32)((vec->y * inverse) >> 32);
    vec->z = (fx32)((vec->z * inverse) >> 32);
}
