#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct SegmentShapeRef SegmentShapeRef;

extern BOOL TestSphereAgainstSegment(SphereShapeRef *sphereRef, SegmentShapeRef *segmentRef, void *hit, u32 flags);

BOOL TestSegmentAgainstSphere(SegmentShapeRef *segmentRef, SphereShapeRef *sphereRef, void *hit, u32 flags)
{
    return TestSphereAgainstSegment(sphereRef, segmentRef, hit, flags ^ 1);
}
