#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct QueryCallback {
    BOOL (*func)();
    void *arg;
} QueryCallback;

typedef struct SweepQuery {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback contact;
    u8 pad_58[8];
} SweepQuery;

typedef struct QueryWorkspace {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct SweepShape {
    void *data;
    s32 bounds[6];
    s32 kind;
    VecFx32 delta;
    s32 sweptBounds[6];
} SweepShape;

typedef struct ShapeExtent {
    VecFx32 center;
    fx32 radius;
} ShapeExtent;

typedef struct QueryMask {
    s32 group;
    s32 layers;
} QueryMask;

typedef struct PathCamera {
    VecFx32 position;
    VecFx32 lookDir;
    VecFx32 upDir;
    VecFx32 anchor;
    VecFx32 targetDir;
    VecFx32 offset;
    fx32 turnRate;
    fx32 followRate;
    s32 freeMove;
} PathCamera;

typedef struct CameraParams {
    u8 pad000[0x134];
    fx32 distance;
} CameraParams;

#define FX_MUL_ROUND(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

extern void Camera_GetRaisedPlayerPosition(VecFx32 *out);
extern u16 GetBiasAdjustedField(int index);
extern unsigned short FX_Atan2Idx(int vertical_component, int horizontal_component);
extern void RotateVectorAroundAxis(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0203ad28(SweepShape *shape, ShapeExtent *extent, VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(s32 *src, s32 *dst, VecFx32 *delta);
extern u32 GetBoundedEntryField(int index);
extern void CollisionQuery_Init(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, QueryMask *mask);
extern void VEC_Normalize(const VecFx32 *in, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void *SweepWorldCollision(SweepQuery *query);
extern fx32 VEC_Mag(const VecFx32 *v);
extern int FX_Mul(int left, int right);
extern int FX_Div(int numer, int denom);
extern BOOL CameraCollision_ShouldBlockFacing();
extern BOOL func_ov050_020c35cc();

void UpdatePathCameraCollision(PathCamera *camera, CameraParams *params)
{
    SweepShape shape;
    QueryWorkspace workspace;
    SweepQuery query;
    SweepShape initShape;
    SweepQuery initQuery;
    VecFx32 raised;
    VecFx32 target;
    ShapeExtent extent;
    VecFx32 shapeDelta;
    VecFx32 side;
    VecFx32 diff;
    VecFx32 axis1;
    VecFx32 axis2;
    VecFx32 axis3;
    VecFx32 delta;
    VecFx32 up;
    VecFx32 axisTmp1;
    VecFx32 axisTmp2;
    VecFx32 axisTmp3;
    VecFx32 deltaTmp;
    VecFx32 upTmp;
    VecFx32 sideTmp;
    VecFx32 sideNorm;
    VecFx32 sideArg;
    VecFx32 cross;
    VecFx32 diffTmp;
    QueryMask mask;
    QueryMask maskTmp;
    QueryCallback filterCb;
    QueryCallback contactCb;
    QueryMask *maskRef;
    void *actor;
    s16 turn;
    s32 angle;
    fx32 length;
    fx32 limit;

    Camera_GetRaisedPlayerPosition(&raised);
    if (camera->freeMove == 0) {
        turn = GetBiasAdjustedField(0) - FX_Atan2Idx(-camera->offset.x, -camera->offset.z);
        if (turn != 0) {
            axisTmp1.x = 0;
            axisTmp1.y = FX32_ONE;
            axisTmp1.z = 0;
            axis1 = axisTmp1;
            angle = (s32)(((s64)-turn * 0x6488) / 0x10000);
            RotateVectorAroundAxis(&camera->offset, &axis1, angle);
            axisTmp2.x = 0;
            axisTmp2.y = FX32_ONE;
            axisTmp2.z = 0;
            axis2 = axisTmp2;
            RotateVectorAroundAxis(&camera->lookDir, &axis2, angle);
            axisTmp3.x = 0;
            axisTmp3.y = FX32_ONE;
            axisTmp3.z = 0;
            axis3 = axisTmp3;
            RotateVectorAroundAxis(&camera->upDir, &axis3, angle);
        }
    }
    VEC_MultAdd(-params->distance, &camera->offset, &raised, &target);
    VEC_Subtract(&target, &raised, &deltaTmp);
    delta = deltaTmp;
    func_0203ad28(&initShape, &extent, &raised, 0x333);
    initShape.delta = delta;
    OffsetBoxByDelta(initShape.bounds, initShape.sweptBounds, &initShape.delta);
    shape = initShape;
    maskTmp.group = 0;
    maskTmp.layers = 0xe;
    mask = maskTmp;
    maskRef = &mask;
    actor = NULL;
    if (GetBoundedEntryField(0) != 0) {
        actor = (void *)(GetBoundedEntryField(0) + 0x14);
    }
    CollisionQuery_Init(&initQuery, 0, actor, 0xf, 1, 1, &shape, &workspace, maskRef);
    query = initQuery;
    filterCb.func = CameraCollision_ShouldBlockFacing;
    filterCb.arg = NULL;
    query.filter = filterCb;
    contactCb.func = func_ov050_020c35cc;
    contactCb.arg = NULL;
    query.contact = contactCb;
    shapeDelta = shape.delta;
    upTmp.x = 0;
    upTmp.y = FX32_ONE;
    upTmp.z = 0;
    up = upTmp;
    sideTmp.x = -FX_MUL_ROUND(camera->offset.z, up.y);
    sideTmp.y = 0;
    sideTmp.z = FX_MUL_ROUND(camera->offset.x, up.y);
    sideArg = sideTmp;
    VEC_Normalize(&sideArg, &sideNorm);
    side = sideNorm;
    VEC_CrossProduct(&shapeDelta, &side, &cross);
    SweepWorldCollision(&query);
    camera->anchor = extent.center;
    if (camera->freeMove == 0) {
        camera->position = camera->anchor;
        return;
    }
    VEC_Subtract(&camera->anchor, &camera->position, &diffTmp);
    diff = diffTmp;
    length = VEC_Mag(&diff);
    if (length != 0) {
        limit = FX_Mul(length, camera->followRate) + 0x29;
        if (length <= limit) {
            camera->position = camera->anchor;
            return;
        }
        VEC_MultAdd(FX_Div(limit, length), &diff, &camera->position, &camera->position);
    }
}
