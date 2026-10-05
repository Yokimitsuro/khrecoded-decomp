#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct PolygonShapeRef PolygonShapeRef;

extern BOOL func_02040038(BoxShapeRef *boxRef, PolygonShapeRef *polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstBox(PolygonShapeRef *polygonRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return func_02040038(boxRef, polygonRef, contact, flags ^ 1);
}
