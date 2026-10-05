#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;
typedef struct CollisionHit CollisionHit;

extern BOOL func_0203f66c(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, CollisionHit *hit, u32 flags);

BOOL TestCylinderAgainstSphere(CylinderShapeRef *cylinderRef, SphereShapeRef *sphereRef, CollisionHit *hit, u32 flags)
{
    return func_0203f66c(sphereRef, cylinderRef, hit, flags ^ 1);
}
