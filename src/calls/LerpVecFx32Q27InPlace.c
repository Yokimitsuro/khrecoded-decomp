#include "nitro/types.h"
#include "nitro/fx_types.h"

void LerpVecFx32Q27InPlace(VecFx32 *current, const VecFx32 *target, s32 t)
{
    /* Blend factor uses 27 fractional bits */
    s32 inverse = 0x8000000 - t;
    current->x = (fx32)(((s64)current->x * inverse) >> 27) + (fx32)(((s64)target->x * t) >> 27);
    current->y = (fx32)(((s64)current->y * inverse) >> 27) + (fx32)(((s64)target->y * t) >> 27);
    current->z = (fx32)(((s64)current->z * inverse) >> 27) + (fx32)(((s64)target->z * t) >> 27);
}
