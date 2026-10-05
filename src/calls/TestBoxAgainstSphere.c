#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct BoxShapeRef BoxShapeRef;

extern BOOL TestSphereAgainstBox(SphereShapeRef *sphereRef, BoxShapeRef *boxRef, void *contact, u32 flags);

BOOL TestBoxAgainstSphere(BoxShapeRef *boxRef, SphereShapeRef *sphereRef, void *contact, u32 flags)
{
    return TestSphereAgainstBox(sphereRef, boxRef, contact, flags ^ 1);
}
