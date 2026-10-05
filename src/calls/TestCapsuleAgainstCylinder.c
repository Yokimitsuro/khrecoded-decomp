#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
    u8 pad_04[0x18];
    s32 kind;
} SphereShapeRef;

extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern BOOL TestSegmentAgainstCylinder(CylinderShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);
extern void GetSegmentDelta(VecFx32 *out, const CollisionCylinder *segment);
extern BOOL func_0204268c(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags, const VecFx32 *velocity);

void TestCapsuleAgainstCylinder(CylinderShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    CollisionCylinder *segment = segmentRef->cylinder;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    VecFx32 velocity;
    SphereShapeRef sphereRef;
    CollisionSphere sphere;

    if ((flags & 2) || (flags & 1) || AreVecsWithinRange16(&segment->start, &segment->end)) {
        TestSegmentAgainstCylinder(segmentRef, cylinderRef, contact, flags);
        return;
    }
    sphereRef.sphere = &sphere;
    sphere.center = segment->start;
    sphere.radius = cylinder->radius;
    GetSegmentDelta(&velocity, segment);
    func_0204268c(&sphereRef, cylinderRef, contact, flags, &velocity);
}
