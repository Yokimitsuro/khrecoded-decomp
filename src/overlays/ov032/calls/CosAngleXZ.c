#include "nitro/fx_types.h"

extern void VEC_Normalize(const VecFx32 *in, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

fx32 CosAngleXZ(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 flatA;
    VecFx32 flatB;

    flatA.x = a->x;
    flatA.y = 0;
    flatA.z = a->z;
    flatB.x = b->x;
    flatB.y = 0;
    flatB.z = b->z;
    if (flatA.x == 0 && flatA.y == 0 && flatA.z == 0) {
        return -0x1000;
    }
    if (flatB.x == 0 && flatB.y == 0 && flatB.z == 0) {
        return -0x1000;
    }
    VEC_Normalize(&flatA, &flatA);
    VEC_Normalize(&flatB, &flatB);
    return VEC_DotProduct(&flatA, &flatB);
}
