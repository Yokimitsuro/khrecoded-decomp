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
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern ComputeBoundsFunc gCollisionBoundsDispatch[];
void ComputePolygonEdgeFrames(CollisionPolygon *polygon);

void InitPolygonShape(CollisionShape *shape, CollisionPolygon *polygon, u8 vertexCount, const VecFx32 *points)
{
    u8 i;

    shape->data = polygon;
    polygon->vertexCount = vertexCount;
    /* Vertex zero is stored after the kind */
    for (i = 1; i < vertexCount; i++)
        polygon->vertices[i].position = points[i];
    shape->kind = 5;
    ((CollisionPolygon *)shape->data)->vertices[0].position = points[0];
    gCollisionBoundsDispatch[5](shape, shape->bounds);
    ComputePolygonEdgeFrames(polygon);
}
