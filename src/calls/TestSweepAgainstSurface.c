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

extern BOOL TestSweepAgainstFaceBounds(const CollTarget *target, const CollSweep *sweep, s32 mode, CollHit *hit);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline BOOL BoxesOverlap(const CollBox *a, const CollBox *b)
{
    return a->maxX >= b->minX && a->minX <= b->maxX
        && a->maxZ >= b->minZ && a->minZ <= b->maxZ
        && a->maxY >= b->minY && a->minY <= b->maxY;
}

BOOL TestSweepAgainstSurface(const CollSweep *sweep, const CollTargetRef *ref, CollHit *hit)
{
    const CollTarget *target;
    int state;
    VecFx32 difference;
    VecFx32 relative;

    if (ref->kind == 4) {
        target = ref->target;
        if (target->isMoving) {
            if (BoxesOverlap(&sweep->sweepBox, &target->sweep.sweepBox)) {
                if (target->sweep.delta.x == 0 && target->sweep.delta.y == 0 && target->sweep.delta.z == 0) {
                    if (sweep->delta.x == 0 && sweep->delta.y == 0 && sweep->delta.z == 0) {
                        state = 2;
                    } else {
                        relative = sweep->delta;
                        state = 1;
                    }
                } else {
                    VEC_Subtract(&sweep->delta, &target->sweep.delta, &difference);
                    relative = difference;
                    if (relative.x == 0 && relative.y == 0 && relative.z == 0) {
                        state = 2;
                    } else {
                        state = 1;
                    }
                }
            } else {
                state = 0;
            }
            if (state != 0) {
                if (state == 2) {
                    return gCollisionTestDispatch[sweep->shape.kind][target->sweep.shape.kind](
                        &sweep->shape, &target->sweep.shape, hit, 14);
                }
                return gCollisionSweepDispatch[sweep->shape.kind][target->sweep.shape.kind](
                    &sweep->shape, &target->sweep.shape, hit, 12, &relative);
            }
            return FALSE;
        }
        if (BoxesOverlap(&sweep->sweepBox, &target->sweep.shape.box)) {
            if (sweep->delta.x == 0 && sweep->delta.y == 0 && sweep->delta.z == 0) {
                state = 2;
            } else {
                state = 1;
            }
        } else {
            state = 0;
        }
        if (state != 0) {
            if (state == 2) {
                return gCollisionTestDispatch[sweep->shape.kind][target->sweep.shape.kind](
                    &sweep->shape, &target->sweep.shape, hit, 6);
            }
            return gCollisionSweepDispatch[sweep->shape.kind][target->sweep.shape.kind](
                &sweep->shape, &target->sweep.shape, hit, 4, &sweep->delta);
        }
        return FALSE;
    }
    return TestSweepAgainstFaceBounds(ref->target, sweep, 1, hit);
}
