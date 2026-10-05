#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec3Array {
    fx32 axis[3];
} Vec3Array;

typedef struct PolygonVertex {
    Vec3Array position;
    u8 derived[0x24];
} PolygonVertex;

typedef struct CollisionPolygon {
    PolygonVertex vertices[4];
    u8 vertexCount;
} CollisionPolygon;

typedef struct ShapeBounds {
    Vec3Array max;
    Vec3Array min;
} ShapeBounds;

typedef struct CollisionShape {
    CollisionPolygon *data;
} CollisionShape;

void ComputePolygonBounds(CollisionShape *shape, ShapeBounds *bounds)
{
    CollisionPolygon *polygon = shape->data;
    u8 vertex;
    u8 axis;
    u8 count;

    /* Seed from vertex zero, then widen */
    bounds->max = polygon->vertices[0].position;
    bounds->min = bounds->max;
    count = polygon->vertexCount;
    for (vertex = 1; vertex < count; vertex++) {
        for (axis = 0; axis < 3; axis++) {
            fx32 value = polygon->vertices[vertex].position.axis[axis];
            if (bounds->max.axis[axis] < value)
                bounds->max.axis[axis] = value;
            else if (bounds->min.axis[axis] > value)
                bounds->min.axis[axis] = value;
        }
    }
}

