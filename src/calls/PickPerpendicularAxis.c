#include "nitro/types.h"
#include "nitro/fx_types.h"

#define IS_NEAR(value) ((value) < 0x10 && (value) > -0x10)

VecFx32 PickPerpendicularAxis(const VecFx32 *vec)
{
    fx32 x = vec->x;

    if ((!IS_NEAR(x - 0x1000) || !IS_NEAR(x + 0x1000)) && vec->y == 0 && vec->z == 0) {
        VecFx32 up;
        up.x = 0;
        up.y = 0x1000;
        up.z = 0;
        return up;
    } else {
        VecFx32 right;
        right.x = 0x1000;
        right.y = 0;
        right.z = 0;
        return right;
    }
}
