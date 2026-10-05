#include "nitro/types.h"
#include "nitro/fx_types.h"

void MulVecFx32InPlace(VecFx32 *vec, const VecFx32 *scale)
{
    vec->x = (fx32)(((fx64)vec->x * scale->x + 0x800) >> 12);
    vec->y = (fx32)(((fx64)vec->y * scale->y + 0x800) >> 12);
    vec->z = (fx32)(((fx64)vec->z * scale->z + 0x800) >> 12);
}
