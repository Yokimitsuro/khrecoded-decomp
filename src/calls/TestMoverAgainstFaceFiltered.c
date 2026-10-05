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

typedef struct MeshFace {
    fx32 minX;
    fx32 minZ;
    fx32 maxX;
    fx32 maxZ;
    u16 unk_10 : 14;
    u16 disabled : 1;
    u16 isLast : 1;
    u8 pad_12[0x76];
} MeshFace;

typedef struct FaceGeometry {
    u8 pad_00[0xc4];
    VecFx32 normal;
} FaceGeometry;

typedef struct FaceQuery {
    const MeshFace *face;
    void *userData;
} FaceQuery;

typedef BOOL (*FaceFilterFn)(FaceQuery *query, void *context, const CollSweep *sweep, BOOL moving);

typedef struct CollMover {
    u32 flags;
    MeshFace *faces;
    u8 pad_08[0x30];
    CollSweep sweep;
    u8 hasSweep;
    u8 pad_7d[0x1b];
    FaceFilterFn faceFilter;
    void *faceFilterContext;
    u8 pad_a0[0x10];
    const CollSweep *activeSweep;
} CollMover;

typedef BOOL (*ShapeTestFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags, const VecFx32 *delta);

extern const ShapeTestFn gCollisionTestDispatch[][6];
extern const ShapeSweepFn gCollisionSweepDispatch[][6];

extern void func_01ffb3a0(const MeshFace *face, FaceGeometry *geometry, BOOL transformed);

BOOL TestMoverAgainstFaceFiltered(const MeshFace *face, CollMover *mover, CollHit *hit, const CollBox *box, BOOL moving, void *userData, const MeshFace **excluded, u32 excludedCount)
{
    FaceGeometry geometry;
    CollShape faceShape;
    FaceQuery query;
    FaceQuery request;

    if (face->disabled) {
        return FALSE;
    }
    if (excludedCount != 0) {
        u8 i = 0;
        do {
            if (face == excluded[i]) {
                return FALSE;
            }
            i++;
        } while (i < excludedCount);
    }
    if (mover->faceFilter != NULL) {
        request.face = face;
        request.userData = userData;
        query = request;
        if (!mover->faceFilter(&query, mover->faceFilterContext, mover->activeSweep, moving)) {
            return FALSE;
        }
    }
    faceShape.data = &geometry;
    func_01ffb3a0(face, &geometry, mover->hasSweep || mover->activeSweep->shape.kind != 2);
    if (moving) {
        return gCollisionSweepDispatch[mover->activeSweep->shape.kind][5](&mover->activeSweep->shape, &faceShape, hit, 4, &mover->activeSweep->delta);
    }
    return gCollisionTestDispatch[mover->activeSweep->shape.kind][5](&mover->activeSweep->shape, &faceShape, hit, mover->hasSweep ? 6 : 0);
}
