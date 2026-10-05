#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

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

typedef struct CollMover {
    u8 pad_00[0x38];
    CollSweep sweep;
    u8 hasSweep;
    u8 isStatic;
    u8 pad_7E[0x32];
    VecFx32 hitNormal;
    u8 pad_BC[4];
    VecFx32 hitPosition;
    u8 pad_CC[0x18];
    fx32 hitTime;
} CollMover;

typedef BOOL (*ShapeTestFn)(CollShape *shape, CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(CollShape *shape, CollShape *other, CollHit *hit, u32 flags, VecFx32 *delta);

extern ShapeTestFn gCollisionTestDispatch[][6];
extern ShapeSweepFn gCollisionSweepDispatch[][6];

extern void CopyShapeFromTemplate(CollShape *src, CollShape *dst, void *buffer);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32(VecFx32 *vec);
extern void GetPointAlongDirectionQ27(fx32 scale, VecFx32 *direction, VecFx32 *origin, VecFx32 *out);

#define TEST_SHAPES(shape, other, hit, flags) \
    gCollisionTestDispatch[(shape).kind][(other).kind](&(shape), &(other), &(hit), (flags))
#define SWEEP_SHAPES(shape, other, hit, flags, delta) \
    gCollisionSweepDispatch[(shape).kind][(other).kind](&(shape), &(other), &(hit), (flags), (delta))

static inline BOOL BoxesOverlap(const CollBox *a, const CollBox *b)
{
    return a->maxX >= b->minX && a->minX <= b->maxX
        && a->maxZ >= b->minZ && a->minZ <= b->maxZ
        && a->maxY >= b->minY && a->minY <= b->maxY;
}

static inline BOOL IsZeroVec(const VecFx32 *vec)
{
    return vec->x == 0 && vec->y == 0 && vec->z == 0;
}

fx32 SweepMoverWallHit(CollTarget *target, CollMover *mover)
{
    CollHit hit;
    BOOL result;
    int state;
    u8 hasSweep = mover->hasSweep;

    if (target->isMoving) {
        if (!mover->isStatic) {
            CollShape local;
            u8 buffer[208];

            CopyShapeFromTemplate(&target->sweep.shape, &local, buffer);
            if (hasSweep) {
                if (BoxesOverlap(&mover->sweep.sweepBox, &local.box)) {
                    if (IsZeroVec(&mover->sweep.delta)) {
                        state = 2;
                    } else {
                        state = 1;
                    }
                } else {
                    state = 0;
                }
                if (state != 0) {
                    result = state == 2 ? TEST_SHAPES(mover->sweep.shape, local, hit, 6)
                                        : SWEEP_SHAPES(mover->sweep.shape, local, hit, 4, &mover->sweep.delta);
                } else {
                    result = FALSE;
                }
            } else if (BoxesOverlap(&mover->sweep.shape.box, &local.box)) {
                result = TEST_SHAPES(mover->sweep.shape, local, hit, 0);
            } else {
                result = FALSE;
            }
        } else if (hasSweep) {
            VecFx32 difference;
            VecFx32 relative;

            if (BoxesOverlap(&mover->sweep.sweepBox, &target->sweep.sweepBox)) {
                if (IsZeroVec(&target->sweep.delta)) {
                    if (IsZeroVec(&mover->sweep.delta)) {
                        state = 2;
                    } else {
                        relative = mover->sweep.delta;
                        state = 1;
                    }
                } else {
                    func_01ff9e3c(&mover->sweep.delta, &target->sweep.delta, &difference);
                    relative = difference;
                    if (IsZeroVec(&relative)) {
                        state = 2;
                    } else {
                        state = 1;
                    }
                }
            } else {
                state = 0;
            }
            if (state != 0) {
                result = state == 2 ? TEST_SHAPES(mover->sweep.shape, target->sweep.shape, hit, 14)
                                    : SWEEP_SHAPES(mover->sweep.shape, target->sweep.shape, hit, 12, &relative);
            } else {
                result = FALSE;
            }
        } else {
            VecFx32 negated;
            VecFx32 reversed;

            if (BoxesOverlap(&mover->sweep.shape.box, &target->sweep.sweepBox)) {
                if (IsZeroVec(&target->sweep.delta)) {
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
                result = state == 2 ? TEST_SHAPES(mover->sweep.shape, target->sweep.shape, hit, (target->sweep.shape.kind == 2 ? 2 : 0) | 8)
                                    : SWEEP_SHAPES(mover->sweep.shape, target->sweep.shape, hit, 8, &reversed);
            } else {
                result = FALSE;
            }
        }
    } else if (hasSweep) {
        if (BoxesOverlap(&mover->sweep.sweepBox, &target->sweep.shape.box)) {
            if (IsZeroVec(&mover->sweep.delta)) {
                state = 2;
            } else {
                state = 1;
            }
        } else {
            state = 0;
        }
        if (state != 0) {
            result = state == 2 ? TEST_SHAPES(mover->sweep.shape, target->sweep.shape, hit, 6)
                                : SWEEP_SHAPES(mover->sweep.shape, target->sweep.shape, hit, 4, &mover->sweep.delta);
        } else {
            result = FALSE;
        }
    } else if (BoxesOverlap(&mover->sweep.shape.box, &target->sweep.shape.box)) {
        result = TEST_SHAPES(mover->sweep.shape, target->sweep.shape, hit, 0);
    } else {
        result = FALSE;
    }

    if (result) {
        VecFx32 position;

        /* Only walls count: the normal needs a horizontal part. */
        if (hit.normal.x == 0 && hit.normal.z == 0) {
            return -FX32_ONE;
        }
        if (VEC_DotProduct(&hit.normal, &mover->sweep.delta) >= 0) {
            return -FX32_ONE;
        }
        hit.time = hit.time < 0 ? 0 : hit.time;
        if (mover->hitTime > hit.time) {
            mover->hitTime = hit.time;
            mover->hitNormal = hit.normal;
            GetPointAlongDirectionQ27(hit.time, &mover->sweep.delta, mover->sweep.shape.origin, &position);
            mover->hitPosition = position;
            return mover->hitTime;
        }
    }
    return -FX32_ONE;
}
