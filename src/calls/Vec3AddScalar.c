#include "nitro/fx_types.h"

void Vec3AddScalar(VecFx32 *v, fx32 amount)
{
    v->x = v->x + amount;
    v->y = v->y + amount;
    v->z = v->z + amount;
}
