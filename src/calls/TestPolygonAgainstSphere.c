#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct PolygonShapeRef PolygonShapeRef;

extern BOOL TestSphereAgainstPolygon(SphereShapeRef *sphereRef, PolygonShapeRef *polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstSphere(PolygonShapeRef *polygonRef, SphereShapeRef *sphereRef, void *contact, u32 flags)
{
    return TestSphereAgainstPolygon(sphereRef, polygonRef, contact, flags ^ 1);
}
