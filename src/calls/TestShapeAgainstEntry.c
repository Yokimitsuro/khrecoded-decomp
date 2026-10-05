#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollShape {
    VecFx32 *origin;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollHit {
    s32 unk_00;
    VecFx32 normal;
    fx32 time;
    s32 unk_14;
} CollHit;

typedef struct CollTarget {
    u8 pad_00[0xd];
    u8 isMoving;
    u8 pad_0E[0x16];
    CollShape shape;
    VecFx32 delta;
} CollTarget;

typedef struct CollEntry {
    CollTarget *target;
    s32 type;
} CollEntry;

typedef BOOL (*ShapeTestFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags, const VecFx32 *delta);

extern ShapeTestFn gCollisionTestDispatch[][6];
extern ShapeSweepFn gCollisionSweepDispatch[][6];

extern void NegateVecFx32(VecFx32 *vec);
extern BOOL TestSweepAgainstFace(const CollTarget *target, const CollShape *shape, s32 mode, CollHit *hit);

BOOL TestShapeAgainstEntry(const CollShape *shape, const CollEntry *entry, CollHit *hit)
{
    const CollTarget *target;
    BOOL moving;
    const VecFx32 *reverseDelta;
    VecFx32 negated;

    if (entry->type == 4) {
        target = entry->target;
        if (target->isMoving) {
            moving = !(target->delta.x == 0 && target->delta.y == 0 && target->delta.z == 0);
            if (moving) {
                VecFx32 delta = target->delta;

                NegateVecFx32(&delta);
                negated = delta;
                reverseDelta = &negated;
            } else {
                reverseDelta = NULL;
            }
            target = entry->target;
            if (!moving) {
                return gCollisionTestDispatch[shape->kind][target->shape.kind](shape, &target->shape, hit, (target->shape.kind == 2 ? 2 : 0) | 8);
            }
            return gCollisionSweepDispatch[shape->kind][target->shape.kind](shape, &target->shape, hit, 8, reverseDelta);
        }
        return gCollisionTestDispatch[shape->kind][target->shape.kind](shape, &target->shape, hit, 0);
    }
    return TestSweepAgainstFace(entry->target, shape, 0, hit);
}
