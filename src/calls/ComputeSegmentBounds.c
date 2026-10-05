#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
} CollisionSegment;

typedef struct ShapeBounds {
    VecFx32 max;
    VecFx32 min;
} ShapeBounds;

typedef struct CollisionShape {
    CollisionSegment *data;
} CollisionShape;

void ComputeSegmentBounds(CollisionShape *shape, ShapeBounds *bounds)
{
    CollisionSegment *segment = shape->data;

    /* Start from the first endpoint, then widen */
    bounds->max = segment->start;
    bounds->min = bounds->max;
    if (bounds->max.x < segment->end.x)
        bounds->max.x = segment->end.x;
    if (bounds->max.y < segment->end.y)
        bounds->max.y = segment->end.y;
    if (bounds->max.z < segment->end.z)
        bounds->max.z = segment->end.z;
    if (bounds->min.x > segment->end.x)
        bounds->min.x = segment->end.x;
    if (bounds->min.y > segment->end.y)
        bounds->min.y = segment->end.y;
    if (bounds->min.z > segment->end.z)
        bounds->min.z = segment->end.z;
}
