#include "nitro/types.h"
#include "nitro/fx_types.h"

void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale)
{
    vec->x = (fx32)(((fx64)vec->x * scale + 0x800) >> 12);
    vec->y = (fx32)(((fx64)vec->y * scale + 0x800) >> 12);
    vec->z = (fx32)(((fx64)vec->z * scale + 0x800) >> 12);
}
