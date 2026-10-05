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

extern VecFx32 func_0204b618(s32 count, ...);

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
        return func_0204b618(2, &shape->data->start, &shape->data->end);
    }
    return shape->data->start;
}
