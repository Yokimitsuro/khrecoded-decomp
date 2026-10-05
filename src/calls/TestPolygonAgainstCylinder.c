#include "nitro/types.h"

typedef struct CylinderShapeRef CylinderShapeRef;
typedef struct CollisionPolygon CollisionPolygon;

extern BOOL TestCylinderAgainstPolygon(CylinderShapeRef *cylinderRef, CollisionPolygon **polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstCylinder(CollisionPolygon **polygonRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    return TestCylinderAgainstPolygon(cylinderRef, polygonRef, contact, flags ^ 1);
}
