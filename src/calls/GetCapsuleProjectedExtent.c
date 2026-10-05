#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCapsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 axis;
    fx32 length;
    fx32 radius;
    fx32 sine;
} CollisionCapsule;

void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
fx32 ComputeOneMinusSquareFraction(fx32 value);

fx32 GetCapsuleProjectedExtent(const CollisionCapsule *capsule, const VecFx32 *axis)
{
    VecFx32 direction;
    VecFx32 delta;
    fx32 length;
    fx32 cosine;
    fx32 radius;
    fx32 sine;

    VEC_Subtract(&capsule->end, &capsule->start, &delta);
    direction = delta;
    length = func_01ffaff4(&direction, &direction);
    cosine = AbsDotProduct(&direction, axis);
    radius = capsule->radius;
    /* Radius times sine plus half length times cosine */
    sine = ComputeOneMinusSquareFraction(cosine);
    return (fx32)(((s64)sine * radius + 0x800) >> 12) +
           (fx32)(((s64)(length / 2) * cosine + 0x800) >> 12);
}


