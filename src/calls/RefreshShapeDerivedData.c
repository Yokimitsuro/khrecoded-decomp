#include "nitro/types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

extern ComputeBoundsFunc gCollisionBoundsDispatch[];
void UpdateBoxAxisAlignedFlag(void *box);
void InitSegmentFromEndpoints(void *segment);
void ComputePolygonEdgeFrames(void *mesh);

void RefreshShapeDerivedData(CollisionShape *shape)
{
    switch (shape->kind) {
    case 0:
        break;
    case 1:
        UpdateBoxAxisAlignedFlag(shape->data);
        break;
    case 2:
        InitSegmentFromEndpoints(shape->data);
        break;
    case 3:
        InitSegmentFromEndpoints(shape->data);
        break;
    case 4:
        InitSegmentFromEndpoints(shape->data);
        break;
    case 5:
        ComputePolygonEdgeFrames(shape->data);
        break;
    }
    /* Recompute bounds for this shape kind */
    gCollisionBoundsDispatch[shape->kind](shape, shape->bounds);
}
