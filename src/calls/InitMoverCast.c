#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 minX;
    s32 minY;
    s32 minZ;
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

typedef struct CollMover {
    u32 flags;
    u8 pad_04[0xc];
    u8 shapeData[0x28];
    CollSweep sweep;
    u8 hasSweep;
    u8 isStatic;
    u8 pad_7E[2];
    VecFx32 direction;
    u32 ownerId;
    u16 groupMask;
    u8 pad_92[0xdc - 0x92];
    s32 unk_DC;
    u8 pad_E0[4];
    s32 nearestHit;
} CollMover;

typedef struct MoverCastParams {
    const VecFx32 *start;
    const VecFx32 *delta;
    fx32 radius;
    u16 flags;
    u16 groupMask;
    u32 ownerId;
} MoverCastParams;

typedef struct CollHitRecord {
    void *model;
    void *face;
    void *wallFace;
    s32 unk_0C;
    void *target;
    u8 pad_14[0x18];
    s32 nearestDistance;
} CollHitRecord;

extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollShape func_0203ade0(void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern CollShape func_0203ad28(void *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const CollBox *src, CollBox *dst, const VecFx32 *delta);
extern CollHitRecord data_027e0134;

void InitMoverCast(CollMover *mover, const MoverCastParams *params)
{
    if (params->radius == 0) {
        VecFx32 end;
        VecFx32 sum;
        CollShape shape;
        VecFx32 diff;
        VecFx32 axis;
        const VecFx32 *start;
        fx32 length;

        func_01ff9e0c(params->start, params->delta, &sum);
        end = sum;
        start = params->start;
        func_01ff9e3c(&end, start, &diff);
        axis = diff;
        length = func_01ffaff4(&axis, &axis);
        shape = func_0203ade0(mover->shapeData, start, &end, &axis, length);
        mover->sweep.shape = shape;
        mover->hasSweep = FALSE;
    } else {
        CollSweep sweep;
        const VecFx32 *delta = params->delta;

        sweep.shape = func_0203ad28(mover->shapeData, params->start, params->radius);
        sweep.delta = *delta;
        OffsetBoxByDelta(&sweep.shape.box, &sweep.sweepBox, &sweep.delta);
        mover->sweep = sweep;
        mover->hasSweep = TRUE;
    }
    mover->flags = params->flags;
    mover->nearestHit = 0x50000000;
    mover->ownerId = params->ownerId;
    mover->groupMask = params->groupMask;
    mover->unk_DC = 0;
    mover->direction = *params->delta;
    mover->isStatic = TRUE;
    data_027e0134.face = NULL;
    data_027e0134.wallFace = NULL;
    data_027e0134.unk_0C = 0;
    data_027e0134.target = NULL;
    data_027e0134.nearestDistance = 0x7fffffff;
}
