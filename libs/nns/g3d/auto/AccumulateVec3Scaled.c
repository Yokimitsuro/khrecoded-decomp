#include "libs/nns/g3d/g3d_glbstate_internal.h"

void AccumulateVec3Scaled(VecFx32 *acc, const VecFx32 *value, fx32 ratio, int isOne)
{
    if (isOne) {
        acc->x += ratio;
        acc->y += ratio;
        acc->z += ratio;
    } else {
        acc->x += (ratio * value->x) >> 12;
        acc->y += (ratio * value->y) >> 12;
        acc->z += (ratio * value->z) >> 12;
    }
}
