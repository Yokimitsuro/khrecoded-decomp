#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;
typedef struct CollisionHit CollisionHit;

extern BOOL TestSphereAgainstCylinder(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, CollisionHit *hit, u32 flags);

BOOL TestCylinderAgainstSphere(CylinderShapeRef *cylinderRef, SphereShapeRef *sphereRef, CollisionHit *hit, u32 flags)
{
    return TestSphereAgainstCylinder(sphereRef, cylinderRef, hit, flags ^ 1);
}
