#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    u8 pad_2C[0xc];
} CameraView;

typedef struct CameraTracking {
    u8 pad_00[0x4];
    int state;
    u8 pad_08[0x4];
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    VecFx32 prevTarget;
    VecFx32 unk_54;
    VecFx32 unk_60;
    VecFx32 unk_6C;
    u32 unk_78;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
    u8 pad_A4[0x14];
    u16 unk_B8;
    u16 unk_BA;
    fx32 unk_BC;
    u8 pad_C0[0x4];
    fx32 unk_C4;
    u8 pad_C8[0x4];
    fx32 unk_CC;
    u8 pad_D0[0x28];
    int turnTimer;
} CameraTracking;

typedef struct CameraBox {
    VecFx32 max;
    VecFx32 min;
} CameraBox;

typedef struct CameraManager {
    CameraView view;
    VecFx32 eye;
    VecFx32 unk_44;
    u8 pad_50[0x94];
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    u8 pad_F4[0x4];
    CameraBox bounds;
    u8 pad_110[0x2c];
    CameraTracking tracking;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;


typedef struct MeshFilter {
    int unk_00;
    int unk_04;
} MeshFilter;

typedef struct MeshQuery {
    u32 words[24];
} MeshQuery;

extern VecFx32 *Camera_GetFocusPosition(void);
extern fx32 Camera_ComputeFollowDistance(int mode);
extern VecFx32 GetNormalizedAxisRejectionMasked(const VecFx32 *vec, const VecFx32 *axis, s32 skipHorizontal);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int MaxOfInts(int count, ...);
extern int MinOfInts(int count, ...);
extern void Vec3AddScalar(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar(VecFx32 *v, fx32 amount);
extern BOOL CachedBounds_NeedsRefresh(CameraBox *cached, const CameraBox *query);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u32 GetBoundedEntryField(int index);
extern void AttachToAnchor(MeshQuery *self, u16 kind, void *anchor, u8 flag, CameraBox *bounds, MeshFilter *filter);
extern void TestQueryAgainstWorldMeshes(MeshQuery *query);

void Camera_RefreshCollisionBounds(CameraTracking *tracking, CameraManager *camera)
{
    MeshQuery request;
    MeshQuery query;
    CameraBox box;
    VecFx32 eye;
    VecFx32 focus;
    VecFx32 marginCopy;
    VecFx32 back;
    VecFx32 upCopy;
    VecFx32 up;
    VecFx32 margin;
    VecFx32 grown;
    VecFx32 shrunk;
    MeshFilter filterCopy;
    MeshFilter filter;
    VecFx32 *focusPos = Camera_GetFocusPosition();
    fx32 distance = Camera_ComputeFollowDistance(camera->mode);
    u32 anchor;
    MeshFilter *filterArg;

    focus = *focusPos;
    anchor = 0;
    focus.y -= distance;
    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    upCopy = up;
    back = GetNormalizedAxisRejectionMasked(&tracking->unk_54, &upCopy, 1);
    VEC_MultAdd(-distance, &back, &tracking->target, &eye);
    box.max.x = MaxOfInts(4, tracking->lookAt.x, eye.x, tracking->prevLookAt.x, focus.x);
    box.max.y = MaxOfInts(5, tracking->lookAt.y, eye.y, tracking->prevLookAt.y, focus.y, tracking->target.y + distance);
    box.max.z = MaxOfInts(4, tracking->lookAt.z, eye.z, tracking->prevLookAt.z, focus.z);
    box.min.x = MinOfInts(4, tracking->lookAt.x, eye.x, tracking->prevLookAt.x, focus.x);
    box.min.y = MinOfInts(4, tracking->lookAt.y, eye.y, tracking->prevLookAt.y, focus.y);
    box.min.z = MinOfInts(4, tracking->lookAt.z, eye.z, tracking->prevLookAt.z, focus.z);
    Vec3AddScalar(&box.max, 0x666);
    Vec3SubScalar(&box.min, 0x666);
    if (CachedBounds_NeedsRefresh(&camera->bounds, &box)) {
        margin.x = 0x2000;
        margin.y = 0x2000;
        margin.z = 0x2000;
        marginCopy = margin;
        VEC_Add(&box.max, &marginCopy, &grown);
        camera->bounds.max = grown;
        VEC_Subtract(&box.min, &marginCopy, &shrunk);
        camera->bounds.min = shrunk;
        filter.unk_00 = 0;
        filter.unk_04 = 0xe;
        filterCopy = filter;
        filterArg = &filterCopy;
        if (GetBoundedEntryField(0)) {
            anchor = GetBoundedEntryField(0) + 0x14;
        }
        AttachToAnchor(&query, 0, (void *)anchor, 0xf, &camera->bounds, filterArg);
        request = query;
        TestQueryAgainstWorldMeshes(&request);
    }
}

