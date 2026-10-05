#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsPointWithinEntityRadius(int entity, const VecFx32 *point)
{
    fx32 distance;

    if ((*(u32 *)(entity + 0x18) & 0x80000000) != 0) {
        return 1;
    }
    distance = VEC_Distance(point, (const VecFx32 *)(entity + 0x24));
    if (distance <= *(int *)(entity + 0x18)) {
        return 1;
    }
    return 0;
}
