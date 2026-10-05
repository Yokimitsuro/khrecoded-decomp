#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} CollisionBox;

void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void GetBoxEdgeMidpointOffset(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out)
{
    /* Edge bits pick the sign of each axis */
    fx32 scale = box->halfExtents[axisA] * ((edge & 1) ? 1 : -1);
    VecFx32 direction = box->axes[axisA];
    ScaleVecFx32InPlace(&direction, scale);
    *out = direction;
    VEC_MultAdd(box->halfExtents[axisB] * ((edge & 2) ? 1 : -1), &box->axes[axisB], out, out);
}
