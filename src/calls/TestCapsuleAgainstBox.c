#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct CapsuleShapeRef CapsuleShapeRef;

extern BOOL func_0203fdf4(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags);

BOOL TestCapsuleAgainstBox(CapsuleShapeRef *capsuleRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return func_0203fdf4(boxRef, capsuleRef, contact, flags ^ 1);
}
