#include "nitro/fx_types.h"

void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}
