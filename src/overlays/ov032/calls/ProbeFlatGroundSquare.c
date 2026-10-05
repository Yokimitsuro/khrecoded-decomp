#include "nitro/fx_types.h"

extern BOOL ProbeGroundBelow(const VecFx32 *origin, fx32 length, VecFx32 *hitPoint);

BOOL ProbeFlatGroundSquare(const VecFx32 *center, fx32 length, VecFx32 *out)
{
    VecFx32 corners[4];
    u32 i;

    for (i = 0; i < 4; i++) {
        VecFx32 *corner = &corners[i];
        corner->x = (i & 1) ? center->x + 0xc00 : center->x - 0xc00;
        corner->z = ((int)i / 2) ? center->z + 0xc00 : center->z - 0xc00;
        corner->y = center->y;
        if (!ProbeGroundBelow(corner, length, corner)) {
            return FALSE;
        }
        if ((int)i > 0 && corner->y != corners[i - 1].y) {
            return FALSE;
        }
    }
    *out = *center;
    out->y = corners[0].y;
    return TRUE;
}
