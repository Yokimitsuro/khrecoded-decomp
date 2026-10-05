#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

void CrossProductFx32Fx16Out(const VecFx32 *a, const VecFx16 *b, VecFx32 *out)
{
    VecFx32 tmp;

    tmp.x = (fx32)(((s64)a->y * b->z - (s64)a->z * b->y + 0x800) >> 12);
    tmp.y = (fx32)(((s64)a->z * b->x - (s64)a->x * b->z + 0x800) >> 12);
    tmp.z = (fx32)(((s64)a->x * b->y - (s64)a->y * b->x + 0x800) >> 12);
    *out = tmp;
}
