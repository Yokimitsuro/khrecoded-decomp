#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} OrientedBox;

extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);

static inline fx32 MulRound(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

fx32 ProjectObbExtentExcludingAxis(OrientedBox *box, const VecFx32 *direction, int excludedAxis)
{
    fx32 total = 0;
    int step;
    if (box->flags & 1) {
        for (step = 1; step <= 2; step++) {
            u8 axis = (u8)((excludedAxis + step) % 3);
            fx32 component = ((fx32 *)direction)[axis];
            fx32 extent = box->halfExtents[axis];
            if (component < 0) {
                component = -component;
            }
            total += MulRound(component, extent);
        }
    } else {
        for (step = 1; step <= 2; step++) {
            u8 axis = (u8)((excludedAxis + step) % 3);
            fx32 extent = box->halfExtents[axis];
            total += MulRound(AbsDotProduct(direction, &box->axes[axis]), extent);
        }
    }
    return total;
}
