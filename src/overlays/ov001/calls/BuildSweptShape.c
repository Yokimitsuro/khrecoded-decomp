#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionShape func_0203ad28(void *storage, const VecFx32 *center, fx32 radius);
extern CollisionShape InitCapsuleShape(void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern CollisionShape InitCylinderShape(void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);

static inline void MakeCapsule(CollisionShape *shape, void *storage, const VecFx32 *position, const VecFx32 *axis, fx32 length, fx32 radius)
{
    VecFx32 tip;
    VecFx32 end;
    VEC_MultAdd(length, axis, position, &end);
    tip = end;
    *shape = InitCapsuleShape(storage, position, &tip, axis, length, radius);
}

static inline void MakeCylinder(CollisionShape *shape, void *storage, const VecFx32 *position, const VecFx32 *axis, fx32 length, fx32 radius)
{
    VecFx32 tip;
    VecFx32 end;
    VEC_MultAdd(length, axis, position, &end);
    tip = end;
    *shape = InitCylinderShape(storage, position, &tip, axis, length, radius);
}

static inline CollisionShape SweepCapsule(void *storage, const VecFx32 *position, const VecFx32 *axis, fx32 length, fx32 radius)
{
    CollisionShape shape;
    VecFx32 end;
    VecFx32 tip;
    VEC_MultAdd(length, axis, position, &end);
    tip = end;
    shape = InitCapsuleShape(storage, position, &tip, axis, length, radius);
    return shape;
}

static inline CollisionShape SweepCylinder(void *storage, const VecFx32 *position, const VecFx32 *axis, fx32 length, fx32 radius)
{
    CollisionShape shape;
    VecFx32 end;
    VecFx32 tip;
    VEC_MultAdd(length, axis, position, &end);
    tip = end;
    shape = InitCylinderShape(storage, position, &tip, axis, length, radius);
    return shape;
}

void BuildSweptShape(SweptShape *out, void *storage, int kind, const VecFx32 *position, const VecFx32 *delta, const VecFx32 *axis, fx32 radius, fx32 length)
{
    VecFx32 up;

    if (axis == NULL) {
        up.x = 0;
        up.y = FX32_ONE;
        up.z = 0;
        axis = &up;
    }
    if (delta == NULL) {
        switch (kind) {
        case 0:
            out->shape = func_0203ad28(storage, position, radius);
            return;
        case 3:
            MakeCapsule(&out->shape, storage, position, axis, length, radius);
            return;
        case 4:
            MakeCylinder(&out->shape, storage, position, axis, length, radius);
            return;
        case 5:
            MakeCylinder(&out->shape, storage, position, axis, length, radius);
            return;
        }
    } else {
        switch (kind) {
        case 0: {
            SweptShape swept;
            swept.shape = func_0203ad28(storage, position, radius);
            swept.delta = *delta;
            OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            *out = swept;
            return;
        }
        case 3: {
            SweptShape swept;
            swept.shape = SweepCapsule(storage, position, axis, length, radius);
            swept.delta = *delta;
            OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            *out = swept;
            return;
        }
        case 4: {
            SweptShape swept;
            swept.shape = SweepCylinder(storage, position, axis, length, radius);
            swept.delta = *delta;
            OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            *out = swept;
            return;
        }
        }
    }
}





