#include "nitro/types.h"

typedef struct CylinderShapeRef CylinderShapeRef;

extern BOOL func_020410b4(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags);

BOOL TestCylinderAgainstCylinderSwapped(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags)
{
    return func_020410b4(refB, refA, contact, flags ^ 1);
}
