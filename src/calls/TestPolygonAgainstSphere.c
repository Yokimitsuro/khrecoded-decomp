#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct PolygonShapeRef PolygonShapeRef;

extern BOOL func_0203fa4c(SphereShapeRef *sphereRef, PolygonShapeRef *polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstSphere(PolygonShapeRef *polygonRef, SphereShapeRef *sphereRef, void *contact, u32 flags)
{
    return func_0203fa4c(sphereRef, polygonRef, contact, flags ^ 1);
}
