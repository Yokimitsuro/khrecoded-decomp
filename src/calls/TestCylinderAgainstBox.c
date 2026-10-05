#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;

extern BOOL func_0203b718(BoxShapeRef *boxRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);

BOOL TestCylinderAgainstBox(CylinderShapeRef *cylinderRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return func_0203b718(boxRef, cylinderRef, contact, flags ^ 1);
}
