#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    SweptShape swept;
    void *owner;
    VecFx32 velocity;
    u8 pad_54[0xc];
} HitRecord;

typedef struct {
    u8 pad_00[4];
    s32 shapeKind;
    u8 pad_08[4];
    fx32 radius;
    fx32 length;
    u8 pad_14[0x3c];
    fx32 altRadius;
} HitShapeDesc;

typedef struct {
    u8 pad_00[2];
    s8 mode;
    u8 pad_03[0x135];
    HitShapeDesc *hitDesc;
    u8 pad_13c[2];
    u8 hitOwner[2];
} HitEntry;

extern u8 data_ov021_020b5658[];
extern u8 data_ov021_020b5694[];
extern u8 data_ov021_020b5668[];

extern void InitRecord60(HitRecord *record);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203ad28(void *storage, const VecFx32 *center, fx32 radius);
extern void InitCapsuleShape(CollisionShape *shape, void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void InitCylinderShape(CollisionShape *shape, void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);

void BuildEntryHitShape(HitEntry *entry, HitRecord *record, const VecFx32 *position, const VecFx32 *velocity)
{
    HitShapeDesc *desc = entry->hitDesc;
    fx32 radius;
    SweptShape sphereSwept;
    SweptShape capsuleSwept;
    SweptShape cylinderSwept;
    VecFx32 start;
    VecFx32 end;
    VecFx32 sphereDelta;
    VecFx32 capsuleAxis;
    VecFx32 capsuleDiff;
    CollisionShape capsuleShape;
    VecFx32 cylinderAxis;
    VecFx32 cylinderDiff;
    CollisionShape cylinderShape;
    VecFx32 cylinderDelta;
    VecFx32 capsuleDelta;

    InitRecord60(record);
    record->velocity = *velocity;
    record->owner = entry->hitOwner;
    if (entry->mode != 2) {
        radius = desc->radius;
    } else {
        radius = desc->altRadius;
    }
    if (radius <= 0) {
        return;
    }
    switch (desc->shapeKind) {
    case 0:
        start = *position;
        sphereDelta = *velocity;
        sphereSwept.shape = func_0203ad28(data_ov021_020b5658, &start, radius);
        sphereSwept.delta = sphereDelta;
        OffsetBoxByDelta(&sphereSwept.shape.bounds, &sphereSwept.sweptBounds, &sphereSwept.delta);
        record->swept = sphereSwept;
        return;
    case 1:
        VEC_MultAdd(desc->length, velocity, position, &end);
        start = *position;
        capsuleDelta = *velocity;
        VEC_Subtract(&end, &start, &capsuleDiff);
        capsuleAxis = capsuleDiff;
        InitCapsuleShape(&capsuleShape, data_ov021_020b5694, &start, &end, &capsuleAxis, func_01ffaff4(&capsuleAxis, &capsuleAxis), radius);
        capsuleSwept.shape = capsuleShape;
        capsuleSwept.delta = capsuleDelta;
        OffsetBoxByDelta(&capsuleSwept.shape.bounds, &capsuleSwept.sweptBounds, &capsuleSwept.delta);
        record->swept = capsuleSwept;
        return;
    case 2:
        start = *position;
        end.x = position->x;
        end.z = position->z;
        end.y = position->y + desc->length;
        cylinderDelta = *velocity;
        VEC_Subtract(&end, &start, &cylinderDiff);
        cylinderAxis = cylinderDiff;
        InitCylinderShape(&cylinderShape, data_ov021_020b5668, &start, &end, &cylinderAxis, func_01ffaff4(&cylinderAxis, &cylinderAxis), radius);
        cylinderSwept.shape = cylinderShape;
        cylinderSwept.delta = cylinderDelta;
        OffsetBoxByDelta(&cylinderSwept.shape.bounds, &cylinderSwept.sweptBounds, &cylinderSwept.delta);
        record->swept = cylinderSwept;
        return;
    }
}
