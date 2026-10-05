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

typedef struct MeshFace {
    fx32 minX;
    fx32 minZ;
    fx32 maxX;
    fx32 maxZ;
    u16 flags;
    u8 pad_12[0x76];
} MeshFace;

typedef struct FaceGeometry {
    u8 pad_00[0xc4];
    VecFx32 normal;
} FaceGeometry;

typedef struct CollMover {
    u32 flags;
    MeshFace *faces;
    u8 pad_08[0x30];
    CollSweep sweep;
    u8 hasSweep;
    u8 pad_7d[0x67];
    fx32 bestTime;
} CollMover;

typedef BOOL (*ShapeTestFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags, const VecFx32 *delta);

extern const ShapeTestFn gCollisionTestDispatch[][6];
extern const ShapeSweepFn gCollisionSweepDispatch[][6];

extern BOOL OverlapsHeightRange(const MeshFace *face, const CollBox *box);
extern void func_01ffb3a0(const MeshFace *face, FaceGeometry *geometry, BOOL transformed);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

fx32 TestMoverAgainstFace(const MeshFace *face, CollMover *mover, CollHit *hit, const CollBox *box)
{
    FaceGeometry geometry;
    CollShape faceShape;
    VecFx32 direction;
    VecFx32 difference;
    BOOL result;
    fx32 time;

    if (!OverlapsHeightRange(face, box)) {
        return -FX32_ONE;
    }
    faceShape.data = &geometry;
    func_01ffb3a0(face, &geometry, mover->hasSweep || mover->sweep.shape.kind != 2);
    if (mover->hasSweep) {
        result = gCollisionSweepDispatch[mover->sweep.shape.kind][5](&mover->sweep.shape, &faceShape, hit, 4, &mover->sweep.delta);
    } else {
        result = gCollisionTestDispatch[mover->sweep.shape.kind][5](&mover->sweep.shape, &faceShape, hit, 0);
    }
    if (result) {
        time = hit->time;
        if (time < 0) {
            time = 0;
        }
        hit->time = time;
        if (mover->bestTime > time && (mover->hasSweep || mover->sweep.shape.kind == 2)
            && VEC_DotProduct(&geometry.normal, &hit->normal) > 0) {
            if (mover->hasSweep) {
                if (VEC_DotProduct(&mover->sweep.delta, &hit->normal) > 0) {
                    return -FX32_ONE;
                }
            } else {
                const VecFx32 *segment = mover->sweep.shape.data;
                VEC_Subtract(&segment[1], &segment[0], &difference);
                direction = difference;
                if (VEC_DotProduct(&direction, &hit->normal) > 0) {
                    return -FX32_ONE;
                }
            }
            return mover->bestTime = hit->time;
        }
    }
    return -FX32_ONE;
}
