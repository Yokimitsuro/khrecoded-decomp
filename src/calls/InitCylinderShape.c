#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern ComputeBoundsFunc gCollisionBoundsDispatch[];

void InitCylinderShape(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                const VecFx32 *direction, fx32 length, fx32 radius)
{
    shape->data = cylinder;
    cylinder->direction = *direction;
    cylinder->length = length;
    cylinder->end = *end;
    cylinder->radius = radius;
    shape->kind = 4;
    ((CollisionCylinder *)shape->data)->start = *start;
    gCollisionBoundsDispatch[4](shape, shape->bounds);
}
