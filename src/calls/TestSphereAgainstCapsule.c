#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

typedef struct CollisionCapsule {
    CollisionSegment segment;
    fx32 radius;
} CollisionCapsule;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

extern BOOL func_0203f2fc(CollisionShape *sphereShape, CollisionShape *segmentShape, CollisionHit *hit, u32 flags);

BOOL TestSphereAgainstCapsule(CollisionShape *sphereShape, CollisionShape *capsuleShape, CollisionHit *hit, u32 flags)
{
    CollisionSphere sphere;
    CollisionSegment segment;
    CollisionShape sphereRef;
    CollisionShape segmentRef;

    sphere = *(CollisionSphere *)sphereShape->data;
    segment = *(CollisionSegment *)capsuleShape->data;
    sphereRef.data = &sphere;
    segmentRef.data = &segment;
    sphere.radius += ((CollisionCapsule *)capsuleShape->data)->radius;
    return func_0203f2fc(&sphereRef, &segmentRef, hit, flags | 0x10);
}
