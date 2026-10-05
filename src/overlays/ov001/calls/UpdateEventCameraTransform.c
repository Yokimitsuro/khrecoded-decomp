#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RotationMtx {
    fx32 m[4][3];
} RotationMtx;

typedef struct CameraLens {
    fx32 zoom;
    fx32 tilt;
    u8 pad_08[4];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 pivot;
    VecFx32 eye;
} CameraLens;

typedef struct EventCameraManager {
    u8 pad_00[0x38];
    VecFx32 offset;
    s32 pitch;
    s32 yaw;
    u8 pad_4c[0x80 - 0x4c];
    fx32 distance;
    u8 pad_84[0x9c - 0x84];
    u32 followActorId;
    u8 pad_a0[0x140 - 0xa0];
    u8 transform[0x10];
    CameraLens lens;
} EventCameraManager;

typedef struct FollowActor {
    u8 pad_00[0xa8];
    VecFx32 position;
} FollowActor;

extern EventCameraManager *data_ov001_020a0514;
extern FollowActor *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Transform_SetBasePos(void *transform, const VecFx32 *pos);
extern void CamAnim_Update(void *transform);
extern void func_ov001_0208af74(RotationMtx *mtx, u16 yaw, u16 pitch);
extern void MTX_MultVec43(const VecFx32 *vec, const RotationMtx *mtx, VecFx32 *dst);
extern void DispatchModeUpdate(CameraLens *lens);

void UpdateEventCameraTransform(void) {
    EventCameraManager *manager = data_ov001_020a0514;
    VecFx32 base;
    RotationMtx rotation;

    if (manager->followActorId != (u32)-1) {
        base = ActorRegistry_GetEntityByIndex(manager->followActorId)->position;
        VEC_Add(&base, &manager->offset, &base);
    } else {
        base = manager->offset;
    }
    Transform_SetBasePos(manager->transform, &base);
    CamAnim_Update(manager->transform);
    if (manager->pitch != 0 || manager->yaw != 0 || manager->distance != 0) {
        VEC_Subtract(&manager->lens.eye, &manager->lens.pivot, &manager->lens.eye);
        manager->lens.eye.z += manager->distance;
        func_ov001_0208af74(&rotation, manager->yaw, manager->pitch);
        MTX_MultVec43(&manager->lens.eye, &rotation, &manager->lens.eye);
        VEC_Add(&manager->lens.eye, &manager->lens.pivot, &manager->lens.eye);
    }
    if (manager->lens.zoom <= 0) {
        manager->lens.zoom = 1;
    } else if (manager->lens.zoom >= 0x1000) {
        manager->lens.zoom = 0xfff;
    }
    if (manager->lens.tilt <= -0x1000) {
        manager->lens.tilt = -0xfff;
    } else if (manager->lens.tilt >= 0x1000) {
        manager->lens.tilt = 0xfff;
    }
    manager->lens.farClip = 0x6a4000;
    manager->lens.nearClip = 0x19a;
    DispatchModeUpdate(&manager->lens);
}
