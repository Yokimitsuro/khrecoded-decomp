#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Sqrt(fx32 value);
extern void DivideVecByLength(VecFx32 *vec, fx32 length);
extern void NegateVecFx32(VecFx32 *vec);

static inline fx32 VecLengthSquared(const VecFx32 *vec, VecFx32 *scratch)
{
    *scratch = *vec;
    return VEC_DotProduct(scratch, scratch);
}

static inline VecFx32 DividedByLength(VecFx32 vec, fx32 length)
{
    DivideVecByLength(&vec, length);
    return vec;
}

static inline VecFx32 UnitUp(void)
{
    VecFx32 up;
    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    return up;
}

BOOL TestSphereAgainstPoint(const VecFx32 *point, const CollisionSphere *sphere, CollisionHit *hit, u32 flags)
{
    VecFx32 check;
    VecFx32 offset;
    VecFx32 diff;
    fx32 distSq;
    fx32 distance;

    func_01ff9e3c(point, &sphere->center, &diff);
    offset = diff;
    distSq = VecLengthSquared(&diff, &check);
    if (distSq <= (fx32)(((fx64)sphere->radius * sphere->radius + 0x800) >> 12)) {
        if (hit != NULL) {
            distance = FX_Sqrt(distSq);
            hit->depth = sphere->radius - distance;
            hit->kind = 3;
            if (distance != 0) {
                hit->normal = DividedByLength(offset, distance);
                if (flags & 1) {
                    NegateVecFx32(&hit->normal);
                }
            } else {
                hit->normal = UnitUp();
            }
        }
        return TRUE;
    }
    return FALSE;
}
