#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    u8 pad_00[0x18];
    VecFx32 halfExtent;
    VecFx32 center;
} CollisionBox;

BOOL PointInBoxXZ(CollisionBox *box, VecFx32 *point)
{
    fx32 extent = box->halfExtent.x;
    fx32 center;
    fx32 upper;

    if (extent & 0x80000000) {
        return TRUE;
    }
    center = box->center.x;
    upper = center + extent;
    if (center - extent > point->x) {
        goto outside;
    }
    if (upper < point->x) {
        goto outside;
    }
    extent = box->halfExtent.y;
    center = box->center.z;
    upper = center + extent;
    if (center - extent > point->z) {
        goto outside;
    }
    if (upper >= point->z) {
        return TRUE;
    }
outside:
    return FALSE;
}
