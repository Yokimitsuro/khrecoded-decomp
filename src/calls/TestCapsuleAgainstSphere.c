#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct CapsuleShapeRef CapsuleShapeRef;

extern BOOL TestSphereAgainstCapsule(SphereShapeRef *sphereRef, CapsuleShapeRef *capsuleRef, void *hit, u32 flags);

BOOL TestCapsuleAgainstSphere(CapsuleShapeRef *capsuleRef, SphereShapeRef *sphereRef, void *hit, u32 flags)
{
    return TestSphereAgainstCapsule(sphereRef, capsuleRef, hit, flags ^ 1);
}
