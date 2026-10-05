#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct CapsuleShapeRef CapsuleShapeRef;

extern BOOL TestBoxAgainstCapsule(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags);

BOOL TestCapsuleAgainstBox(CapsuleShapeRef *capsuleRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return TestBoxAgainstCapsule(boxRef, capsuleRef, contact, flags ^ 1);
}
