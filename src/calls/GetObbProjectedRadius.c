#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    VecFx32 halfExtents;
    VecFx32 axes[3];
    u8 axisAligned : 1;
} OrientedBox;

int MSL_AbsA(int x);
void ApplyScalarToVec3(VecFx32 *values, int (*transform)(int));
void TransformVectorByBasis(const VecFx32 *vec, const VecFx32 *basis, VecFx32 *out);
fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

fx32 GetObbProjectedRadius(const OrientedBox *box, const VecFx32 *axis)
{
    VecFx32 localAbs;
    VecFx32 worldAbsCopy;
    VecFx32 worldAbs;
    VecFx32 local;

    if (box->axisAligned) {
        worldAbs = *axis;
        ApplyScalarToVec3(&worldAbs, MSL_AbsA);
        worldAbsCopy = worldAbs;
        return VEC_DotProduct(&worldAbsCopy, &box->halfExtents);
    }
    /* Rotate the axis into box space first */
    TransformVectorByBasis(axis, box->axes, &local);
    localAbs = local;
    ApplyScalarToVec3(&localAbs, MSL_AbsA);
    return VEC_DotProduct(&localAbs, &box->halfExtents);
}
