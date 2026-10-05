#include "nitro/types.h"

typedef struct SegmentShapeRef SegmentShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;

extern void TestCapsuleAgainstCylinder(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);

void TestCylinderAgainstSegment(CylinderShapeRef *cylinderRef, SegmentShapeRef *segmentRef, void *contact, u32 flags)
{
    TestCapsuleAgainstCylinder(segmentRef, cylinderRef, contact, flags ^ 1);
}
