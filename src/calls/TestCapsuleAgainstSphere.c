#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct CapsuleShapeRef CapsuleShapeRef;

extern BOOL func_0203f624(SphereShapeRef *sphereRef, CapsuleShapeRef *capsuleRef, void *hit, u32 flags);

BOOL TestCapsuleAgainstSphere(CapsuleShapeRef *capsuleRef, SphereShapeRef *sphereRef, void *hit, u32 flags)
{
    return func_0203f624(sphereRef, capsuleRef, hit, flags ^ 1);
}
