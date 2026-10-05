#include "nitro/types.h"
#include "nitro/fx_types.h"

void ScaleVecComponentsConditional(VecFx32 *vec, s32 scale, s32 skipHorizontal)
{
    if (skipHorizontal == 0) {
        vec->x = vec->x * scale;
        vec->z = vec->z * scale;
    }
    vec->y = vec->y * scale;
}
