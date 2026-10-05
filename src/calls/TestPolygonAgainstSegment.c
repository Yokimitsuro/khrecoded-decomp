#include "nitro/types.h"

typedef struct CollisionSegment CollisionSegment;
typedef struct CollisionPolygon CollisionPolygon;
typedef struct CollisionContact CollisionContact;

extern BOOL func_0203c26c(CollisionSegment **segmentRef, CollisionPolygon **polygonRef, CollisionContact *contact, u32 flags);

BOOL TestPolygonAgainstSegment(CollisionPolygon **polygonRef, CollisionSegment **segmentRef, CollisionContact *contact, u32 flags)
{
    return func_0203c26c(segmentRef, polygonRef, contact, flags ^ 1);
}
