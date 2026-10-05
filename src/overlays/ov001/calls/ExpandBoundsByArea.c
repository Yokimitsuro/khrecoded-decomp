#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AreaShape {
    fx32 minX;
    fx32 minZ;
    fx32 maxX;
    fx32 maxZ;
    u8 pad_10[2];
    u16 pointCount;
    u8 pad_14[0x3c];
    VecFx32 points[1];
} AreaShape;

typedef struct Bounds {
    VecFx32 min;
    VecFx32 max;
} Bounds;

void ExpandBoundsByArea(void *unused, AreaShape *area, Bounds *bounds)
{
    int i;

    if (area->minX < bounds->min.x) {
        bounds->min.x = area->minX;
    }
    if (area->minZ < bounds->min.z) {
        bounds->min.z = area->minZ;
    }
    if (bounds->max.x < area->maxX) {
        bounds->max.x = area->maxX;
    }
    if (bounds->max.z < area->maxZ) {
        bounds->max.z = area->maxZ;
    }
    for (i = 0; i < area->pointCount; i++) {
        if (area->points[i].y < bounds->min.y) {
            bounds->min.y = area->points[i].y;
        }
        if (bounds->max.y < area->points[i].y) {
            bounds->max.y = area->points[i].y;
        }
    }
}
