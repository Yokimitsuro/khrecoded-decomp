#include "nitro/types.h"
#include "nitro/fx_types.h"
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

typedef struct CameraManager {
    u8 pad_00[0x80];
    s32 type;
    u8 pad_84[0xe4 - 0x84];
    s32 followPreset;
    u8 pad_e8[0xf8 - 0xe8];
    u8 buffers[0x13c - 0xf8];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern VecFx32 *Camera_GetFocusPosition(void);
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);
extern void func_ov046_020c1a10(s32 preset);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0203ad28(SweepShape *shape, ShapeExtent *extent, VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(s32 *src, s32 *dst, VecFx32 *delta);
extern u32 GetBoundedEntryField(int index);
extern void CollisionQuery_Init(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, QueryMask *mask);
extern void CopyTransformFields(SweepQuery *query, void *buffers);
extern void *SweepWorldCollision(SweepQuery *query);
extern BOOL CameraCollision_ShouldTestContact();
extern BOOL IsQueryFacingContact_020c1e60();

void Camera_ResolveCollision(VecFx32 *position)
{
    SweepShape shape;
    QueryWorkspace workspace;
    SweepQuery query;
    SweepShape initShape;
    SweepQuery initQuery;
    VecFx32 focus;
    ShapeExtent extent;
    VecFx32 delta;
    VecFx32 focusTmp;
    VecFx32 deltaTmp;
    QueryMask mask;
    QueryMask maskTmp;
    QueryCallback filterCb;
    QueryCallback contactCb;
    QueryMask *maskRef;
    void *actor;
    CameraManager *camera = data_ov046_020c3500;
    void *follow;
    VecFx32 *center;

    follow = camera->type == 0 ? camera->controllerData : NULL;
    if (camera->type == 0) {
        center = Camera_GetFocusPosition();
    } else {
        center = func_ov001_0206dc4c(0);
    }
    func_ov046_020c1a10(camera->followPreset);
    focusTmp.x = center->x;
    focusTmp.y = center->y + FX32_ONE;
    focusTmp.z = center->z;
    focus = focusTmp;
    VEC_Subtract(position, &focus, &deltaTmp);
    delta = deltaTmp;
    func_0203ad28(&initShape, &extent, &focus, 0x4cd);
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
    if (follow != NULL) {
        CopyTransformFields(&query, camera->buffers);
    }
    filterCb.func = CameraCollision_ShouldTestContact;
    filterCb.arg = camera;
    query.filter = filterCb;
    contactCb.func = IsQueryFacingContact_020c1e60;
    contactCb.arg = NULL;
    query.contact = contactCb;
    if (SweepWorldCollision(&query) != NULL) {
        *position = extent.center;
    }
}

