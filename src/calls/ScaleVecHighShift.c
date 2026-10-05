#include "nitro/types.h"
#include "nitro/fx_types.h"

void ScaleVecHighShift(VecFx32 *vec, s32 scale)
{
    vec->x = (s32)(((s64)vec->x * scale) >> 0x1b);
    vec->y = (s32)(((s64)vec->y * scale) >> 0x1b);
    vec->z = (s32)(((s64)vec->z * scale) >> 0x1b);
}
