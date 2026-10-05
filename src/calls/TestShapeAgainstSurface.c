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
    void *data;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

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
    CollSweep sweep;
} CollTarget;

typedef struct CollTargetRef {
    CollTarget *target;
    s32 kind;
} CollTargetRef;

typedef BOOL (*ShapeTestFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags, const VecFx32 *delta);

extern ShapeTestFn gCollisionTestDispatch[][6];
extern ShapeSweepFn gCollisionSweepDispatch[][6];

extern BOOL TestSweepAgainstFaceBounds(const CollTarget *target, const CollShape *shape, s32 mode, CollHit *hit);
extern void NegateVecFx32(VecFx32 *vec);

static inline BOOL BoxesOverlap(const CollBox *a, const CollBox *b)
{
    return a->maxX >= b->minX && a->minX <= b->maxX
        && a->maxZ >= b->minZ && a->minZ <= b->maxZ
        && a->maxY >= b->minY && a->minY <= b->maxY;
}

BOOL TestShapeAgainstSurface(const CollShape *shape, const CollTargetRef *ref, CollHit *hit)
{
    const CollTarget *target;
    int state;
    VecFx32 negated;
    VecFx32 reversed;

    if (ref->kind == 4) {
        target = ref->target;
        if (target->isMoving) {
            if (BoxesOverlap(&shape->box, &target->sweep.sweepBox)) {
                if (target->sweep.delta.x == 0 && target->sweep.delta.y == 0 && target->sweep.delta.z == 0) {
                    state = 2;
                } else {
                    negated = target->sweep.delta;
                    NegateVecFx32(&negated);
                    reversed = negated;
                    state = 1;
                }
            } else {
                state = 0;
            }
            if (state != 0) {
                if (state == 2) {
                    return gCollisionTestDispatch[shape->kind][target->sweep.shape.kind](
                        shape, &target->sweep.shape, hit, (target->sweep.shape.kind == 2 ? 2 : 0) | 8);
                }
                return gCollisionSweepDispatch[shape->kind][target->sweep.shape.kind](
                    shape, &target->sweep.shape, hit, 8, &reversed);
            }
            return FALSE;
        }
        if (BoxesOverlap(&shape->box, &target->sweep.shape.box)) {
            return gCollisionTestDispatch[shape->kind][target->sweep.shape.kind](
                shape, &target->sweep.shape, hit, 0);
        }
        return FALSE;
    }
    return TestSweepAgainstFaceBounds(ref->target, shape, 0, hit);
}
