#include "nitro/types.h"
#include "nitro/fx.h"
#include "nitro/os.h"

void BlendScaleVec (VecFx32 * v0, const VecFx32 * v1, fx32 ratio, BOOL isV1One)
{
    if (isV1One) {

        v0->x += ratio;
        v0->y += ratio;
        v0->z += ratio;
    } else {
        v0->x += ratio * v1->x >> FX32_SHIFT;
        v0->y += ratio * v1->y >> FX32_SHIFT;
        v0->z += ratio * v1->z >> FX32_SHIFT;
    }
}
