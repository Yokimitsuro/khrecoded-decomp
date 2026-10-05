#include "nitro/fx_types.h"

void Vec3MulScalar(VecFx32 *v, fx32 factor)
{
    v->x = v->x * factor;
    v->y = v->y * factor;
    v->z = v->z * factor;
}
