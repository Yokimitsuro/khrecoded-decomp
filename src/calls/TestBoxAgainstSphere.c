#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct BoxShapeRef BoxShapeRef;

extern BOOL func_0203f0b0(SphereShapeRef *sphereRef, BoxShapeRef *boxRef, void *contact, u32 flags);

BOOL TestBoxAgainstSphere(BoxShapeRef *boxRef, SphereShapeRef *sphereRef, void *contact, u32 flags)
{
    return func_0203f0b0(sphereRef, boxRef, contact, flags ^ 1);
}
