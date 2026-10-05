#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct SegmentShapeRef SegmentShapeRef;

extern BOOL func_0203f2fc(SphereShapeRef *sphereRef, SegmentShapeRef *segmentRef, void *hit, u32 flags);

BOOL TestSegmentAgainstSphere(SegmentShapeRef *segmentRef, SphereShapeRef *sphereRef, void *hit, u32 flags)
{
    return func_0203f2fc(sphereRef, segmentRef, hit, flags ^ 1);
}
