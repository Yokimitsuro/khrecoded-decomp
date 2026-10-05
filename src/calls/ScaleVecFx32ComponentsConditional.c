#include "nitro/types.h"
#include "nitro/fx_types.h"

void ScaleVecFx32ComponentsConditional(VecFx32 *vec, fx32 scale, s32 skipHorizontal)
{
    if (skipHorizontal == 0) {
        vec->x = (fx32)(((fx64)vec->x * scale + 0x800) >> 0xc);
        vec->z = (fx32)(((fx64)vec->z * scale + 0x800) >> 0xc);
    }
    vec->y = (fx32)(((fx64)vec->y * scale + 0x800) >> 0xc);
}
