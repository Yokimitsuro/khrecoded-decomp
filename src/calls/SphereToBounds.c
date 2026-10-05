#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

extern void Vec3AddScalar(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar(VecFx32 *v, fx32 amount);

void SphereToBounds(Sphere **spherePtr, VecFx32 *bounds)
{
    Sphere *sphere = *spherePtr;

    bounds[0] = sphere->center;
    bounds[1] = bounds[0];
    Vec3AddScalar(&bounds[0], sphere->radius);
    Vec3SubScalar(&bounds[1], sphere->radius);
}
