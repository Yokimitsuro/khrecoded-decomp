#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Plane {
    fx32 distance;
    VecFx32 normal;
} Plane;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div(fx32 numer, fx32 denom);

void SetPlaneNormalRescaled(Plane *plane, const VecFx32 *normal)
{
    VecFx32 previous;
    fx32 dot;
    fx32 magnitude;

    previous = plane->normal;
    plane->normal = *normal;
    dot = VEC_DotProduct(&plane->normal, &previous);
    magnitude = dot < 0 ? -dot : dot;
    if (magnitude > 0x10) {
        plane->distance = FX_Div(plane->distance, dot);
    }
}
