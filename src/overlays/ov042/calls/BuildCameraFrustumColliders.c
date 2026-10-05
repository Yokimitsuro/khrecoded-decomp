#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    u32 _0;
    Box src;
    u32 shapeType;
    VecFx32 delta;
    Box dst;
    u8 _44[0x44];
} CameraCollider;

typedef struct {
    VecFx32 position;
    VecFx32 edgeDir;
    VecFx32 edgeNormal;
    u8 pad_24[0xc];
} PolygonVertex;

typedef struct {
    PolygonVertex vertices[4];
    u8 vertexCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

typedef struct {
    VecFx32 row[3];
} Basis33;

typedef struct {
    u8 _0[0x10];
    fx32 depth;
    u8 _14[0x40];
    int left;
    int right;
    int top;
    int bottom;
    VecFx32 eye;
    u8 _70[0x12c];
    CollisionPolygon polygons[3];
    u8 _40c[0x24];
    CameraCollider colliders[3];
} CameraState;

typedef void (*ColliderShapeFunc)(CameraCollider *collider, Box *box);

extern CameraState *data_ov042_020be5e0;
extern u8 NNS_G3dGlb_cameraMtx[];
extern ColliderShapeFunc gCollisionBoundsDispatch[];
extern void func_01ff913c(const void *src, Basis33 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void camera_commit_explicit_projection(CameraState *camera, int top, int bottom, int left, int right);
extern void ComputePolygonEdgeFrames(CollisionPolygon *polygon);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);

static inline void RefreshCollider(CameraCollider *collider) {
    gCollisionBoundsDispatch[collider->shapeType](collider, (Box *)((u32 *)collider + 1));
    OffsetBoxByDelta(&collider->src, &collider->dst, &collider->delta);
}

void BuildCameraFrustumColliders(void) {
    CameraState *camera = data_ov042_020be5e0;
    VecFx32 width;
    Basis33 basis;
    VecFx32 corner;
    Basis33 temp;
    VecFx32 point0;
    VecFx32 point1;
    VecFx32 point2;
    VecFx32 point3;
    VecFx32 point4;
    VecFx32 scaled;
    VecFx32 point5;
    VecFx32 point6;
    VecFx32 point7;
    VecFx32 point8;
    VecFx32 point9;
    VecFx32 point10;
    VecFx32 point11;
    VecFx32 point12;
    VecFx32 point13;
    int nearBottom = camera->bottom - 0x1800;
    int farTop = camera->top;
    fx32 span;

    func_01ff913c(NNS_G3dGlb_cameraMtx, &temp);
    basis = temp;
    VEC_MultAdd(camera->left, &basis.row[0], &camera->eye, &point0);
    corner = point0;
    camera_commit_explicit_projection(camera, camera->top, camera->bottom, camera->left, camera->right);

    VEC_MultAdd(nearBottom, &basis.row[1], &corner, &point1);
    camera->polygons[0].vertices[0].position = point1;
    VEC_MultAdd(farTop + 0x64000, &basis.row[1], &corner, &point2);
    camera->polygons[0].vertices[1].position = point2;
    VEC_MultAdd(-camera->depth, &basis.row[2], &camera->polygons[0].vertices[1].position, &point3);
    camera->polygons[0].vertices[2].position = point3;
    VEC_MultAdd(-camera->depth, &basis.row[2], &camera->polygons[0].vertices[0].position, &point4);
    camera->polygons[0].vertices[3].position = point4;
    ComputePolygonEdgeFrames(&camera->polygons[0]);
    RefreshCollider(&camera->colliders[0]);

    span = camera->right - camera->left;
    scaled = basis.row[0];
    ScaleVecFx32InPlace(&scaled, span);
    width = scaled;
    VEC_Add(&camera->polygons[0].vertices[0].position, &width, &point5);
    camera->polygons[1].vertices[0].position = point5;
    VEC_Add(&camera->polygons[0].vertices[1].position, &width, &point6);
    camera->polygons[1].vertices[3].position = point6;
    VEC_Add(&camera->polygons[0].vertices[2].position, &width, &point7);
    camera->polygons[1].vertices[2].position = point7;
    VEC_Add(&camera->polygons[0].vertices[3].position, &width, &point8);
    camera->polygons[1].vertices[1].position = point8;
    ComputePolygonEdgeFrames(&camera->polygons[1]);
    RefreshCollider(&camera->colliders[1]);

    VEC_MultAdd(camera->top, &basis.row[1], &camera->eye, &point9);
    corner = point9;
    VEC_MultAdd(camera->left, &basis.row[0], &corner, &point10);
    camera->polygons[2].vertices[0].position = point10;
    VEC_MultAdd(camera->right, &basis.row[0], &corner, &point11);
    camera->polygons[2].vertices[1].position = point11;
    VEC_MultAdd(-camera->depth, &basis.row[2], &camera->polygons[2].vertices[1].position, &point12);
    camera->polygons[2].vertices[2].position = point12;
    VEC_MultAdd(-camera->depth, &basis.row[2], &camera->polygons[2].vertices[0].position, &point13);
    camera->polygons[2].vertices[3].position = point13;
    ComputePolygonEdgeFrames(&camera->polygons[2]);
    RefreshCollider(&camera->colliders[2]);
}
