#include "nitro/types.h"

typedef struct CylinderShapeRef CylinderShapeRef;
typedef struct CollisionPolygon CollisionPolygon;

extern BOOL func_0203c6d0(CylinderShapeRef *cylinderRef, CollisionPolygon **polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstCylinder(CollisionPolygon **polygonRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    return func_0203c6d0(cylinderRef, polygonRef, contact, flags ^ 1);
}
