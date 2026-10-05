#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_ov032_020bbca0(void *object, int radius, int direction, VecFx32 *offset);
extern void *SweepSphereAgainstWorld(const VecFx32 *origin, u8 layer, fx32 height, const VecFx32 *offset, VecFx32 *hit);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

int FindFarthestOpenDirection(void *object, int radius, const VecFx32 *origin, fx32 height, int startDirection, u32 blockedMask) {
    VecFx32 hit;
    VecFx32 offset;
    int direction = startDirection;
    int bestDirection = -1;
    fx32 bestDistance = -1;
    int step;

    for (step = 0; step < 16; step++) {
        if (!((1 << direction) & blockedMask)) {
            fx32 distance;
            func_ov032_020bbca0(object, radius, direction, &offset);
            SweepSphereAgainstWorld(origin, 7, height, &offset, &hit);
            distance = VEC_DotProduct(&hit, &hit);
            if (distance > bestDistance && distance > 0) {
                bestDirection = direction;
                bestDistance = distance;
            }
        }
        direction = (direction + 1) % 16;
    }
    return bestDirection;
}
