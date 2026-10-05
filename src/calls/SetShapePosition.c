#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PolygonVertex {
    VecFx32 position;
    u8 derived[0x24];
} PolygonVertex;

typedef struct CollisionPolygon {
    PolygonVertex vertices[4];
    u8 vertexCount;
} CollisionPolygon;

typedef struct CollisionShape {
    VecFx32 *data;
    VecFx32 boundsMin;
    VecFx32 boundsMax;
    s32 kind;
} CollisionShape;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    func_01ff9e3c(a, b, &out);
    return out;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    func_01ff9e0c(a, b, &out);
    return out;
}

void SetShapePosition(CollisionShape *shape, const VecFx32 *position)
{
    VecFx32 delta;
    u8 i;
    u8 count;

    delta = SubtractVec(position, shape->data);
    *shape->data = *position;
    func_01ff9e0c(&shape->boundsMax, &delta, &shape->boundsMax);
    func_01ff9e0c(&shape->boundsMin, &delta, &shape->boundsMin);
    switch (shape->kind) {
    case 0:
    case 1:
        break;
    case 2:
    case 3:
    case 4:
        shape->data[1] = AddVec(&shape->data[1], &delta);
        break;
    case 5:
        count = ((CollisionPolygon *)shape->data)->vertexCount;
        for (i = 1; i < count; i++) {
            ((CollisionPolygon *)shape->data)->vertices[i].position = AddVec(&((CollisionPolygon *)shape->data)->vertices[i].position, &delta);
        }
        break;
    }
}
