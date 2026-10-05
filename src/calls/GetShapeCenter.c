#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeEndpoints {
    VecFx32 start;
    VecFx32 end;
} ShapeEndpoints;

typedef struct CollisionShape {
    ShapeEndpoints *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

extern VecFx32 AverageVecs(s32 count, ...);

VecFx32 GetShapeCenter(const CollisionShape *shape)
{
    switch (shape->kind) {
    case 0:
    case 1:
    case 5:
        break;
    case 2:
    case 3:
    case 4:
        return AverageVecs(2, &shape->data->start, &shape->data->end);
    }
    return shape->data->start;
}
