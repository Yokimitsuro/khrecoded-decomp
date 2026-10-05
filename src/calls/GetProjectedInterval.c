#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    u8 pad_0c[0x24];
} ShapeVertex;

typedef struct {
    ShapeVertex vertices[4];
    u8 vertexCount;
} ConvexShape;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

fx32 GetProjectedInterval(ConvexShape *shape, const VecFx32 *axis, fx32 *center)
{
    u8 count;
    u8 i;
    fx32 maxProj;
    fx32 minProj;

    count = shape->vertexCount;
    minProj = VEC_DotProduct(&shape->vertices[0].position, axis);
    maxProj = minProj;
    for (i = 1; i < count; i++) {
        fx32 proj = VEC_DotProduct(&shape->vertices[i].position, axis);
        if (maxProj < proj) {
            maxProj = proj;
        } else if (minProj > proj) {
            minProj = proj;
        }
    }
    *center = (maxProj + minProj) / 2;
    return (maxProj - minProj) / 2;
}
