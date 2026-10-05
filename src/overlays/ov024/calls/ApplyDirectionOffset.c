#include "nitro/types.h"
#include "nitro/fx_types.h"

void ApplyDirectionOffset(fx32 *pos, const VecFx32 *offset, int direction)
{
    switch (direction) {
    case 0:
        pos[0] += offset->x;
        pos[1] += offset->z;
        break;
    case 1:
        pos[0] -= offset->z;
        pos[1] += offset->x;
        break;
    case 2:
        pos[0] -= offset->x;
        pos[1] -= offset->z;
        break;
    case 3:
        pos[0] += offset->z;
        pos[1] -= offset->x;
        break;
    }
}
