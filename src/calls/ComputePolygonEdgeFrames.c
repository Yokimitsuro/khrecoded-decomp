#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PolygonVertex {
    VecFx32 position;
    VecFx32 edgeDir;
    VecFx32 edgeNormal;
    u8 pad_24[0xc];
} PolygonVertex;

typedef struct CollisionPolygon {
    PolygonVertex vertices[4];
    u8 vertexCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);

void ComputePolygonEdgeFrames(CollisionPolygon *polygon)
{
    VecFx32 edgeCopy;
    VecFx32 edge;
    VecFx32 edgeDir;
    VecFx32 normal;
    VecFx32 cross;
    VecFx32 crossCopy;
    VecFx32 edgeNormal;
    u32 count = polygon->vertexCount;
    u8 i;

    for (i = 0; i < count; i++) {
        func_01ff9e3c(&polygon->vertices[(i + 1) % (int)count].position, &polygon->vertices[i].position, &edge);
        edgeCopy = edge;
        VEC_Normalize(&edgeCopy, &edgeDir);
        polygon->vertices[i].edgeDir = edgeDir;
    }
    func_01ff9ea8(&polygon->vertices[1].edgeDir, &polygon->vertices[0].edgeDir, &cross);
    crossCopy = cross;
    VEC_Normalize(&crossCopy, &normal);
    polygon->normal = normal;
    for (i = 0; i < count; i++) {
        PolygonVertex *vertex = &polygon->vertices[i];
        func_01ff9ea8(&polygon->normal, &vertex->edgeDir, &edgeNormal);
        vertex->edgeNormal = edgeNormal;
    }
}
