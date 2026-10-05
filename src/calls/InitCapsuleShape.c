#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCapsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 axis;
    fx32 length;
    fx32 radius;
} CollisionCapsule;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern ComputeBoundsFunc gCollisionBoundsDispatch[];

void InitCapsuleShape(CollisionShape *shape, CollisionCapsule *capsule, const VecFx32 *start, const VecFx32 *end,
                      const VecFx32 *axis, fx32 length, fx32 radius)
{
    shape->data = capsule;
    capsule->axis = *axis;
    capsule->length = length;
    capsule->end = *end;
    capsule->radius = radius;
    capsule->end = *end;
    /* Kind indexes the bounds function table */
    shape->kind = 3;
    ((CollisionCapsule *)shape->data)->start = *start;
    gCollisionBoundsDispatch[3](shape, shape->bounds);
}

