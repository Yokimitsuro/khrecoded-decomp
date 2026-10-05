#include "nitro/types.h"

typedef struct SegmentShapeRef SegmentShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;

extern void func_0204055c(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);

void TestCylinderAgainstSegment(CylinderShapeRef *cylinderRef, SegmentShapeRef *segmentRef, void *contact, u32 flags)
{
    func_0204055c(segmentRef, cylinderRef, contact, flags ^ 1);
}
