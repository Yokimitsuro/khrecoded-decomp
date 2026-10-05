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
    u16 flags;
    u8 pad_12[0x76];
} MeshFace;

typedef struct FaceGeometry {
    u8 pad_00[0xc4];
    VecFx32 normal;
} FaceGeometry;

typedef BOOL (*ShapeTestFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(const CollShape *shape, const CollShape *other, CollHit *hit, u32 flags, const VecFx32 *delta);

extern const ShapeTestFn gCollisionTestDispatch[][6];
extern const ShapeSweepFn gCollisionSweepDispatch[][6];

extern void func_01ffb3a0(const MeshFace *face, FaceGeometry *geometry, BOOL transformed);

BOOL TestSweepAgainstFace(const MeshFace *face, const CollSweep *sweep, BOOL moving, CollHit *hit)
{
    FaceGeometry geometry;
    CollShape faceShape;

    faceShape.data = &geometry;
    func_01ffb3a0(face, &geometry, moving || sweep->shape.kind != 2);
    if (moving) {
        return gCollisionSweepDispatch[sweep->shape.kind][5](&sweep->shape, &faceShape, hit, 4, &sweep->delta);
    }
    return gCollisionTestDispatch[sweep->shape.kind][5](&sweep->shape, &faceShape, hit, 0);
}
