#include "nitro/types.h"

typedef struct CylinderShapeRef CylinderShapeRef;

extern BOOL TestCylinderAgainstCylinder(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags);

BOOL TestCylinderAgainstCylinderSwapped(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags)
{
    return TestCylinderAgainstCylinder(refB, refA, contact, flags ^ 1);
}
