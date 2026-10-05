#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 fov;
} CameraView;

typedef struct CameraSnapshot {
    VecFx32 position;
    VecFx32 direction;
    u8 pad_18[8];
    s32 followPreset;
    fx32 blendScale;
    fx32 blendSpeed;
    s32 state;
} CameraSnapshot;

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
    VecFx32 target;
    u8 pad_50[0xe0 - 0x50];
    u32 optionFlags;
    s32 followPreset;
    s32 prevPreset;
    u8 pad_ec[4];
    u32 state;
    u8 pad_f4[0x12c - 0xf4];
    fx32 blendScale;
    fx32 blendSpeed;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void Camera_BlendToVelocityAim(const VecFx32 *velocity, s32 curveType, fx32 duration);

void Camera_RestoreSnapshot(const CameraSnapshot *snapshot)
{
    CameraView view;
    VecFx32 direction;
    VecFx32 normalized;
    VecFx32 diff;
    VecFx32 dirCopy;
    VecFx32 up;

    if (snapshot->state == 0) {
        VEC_Subtract(&data_ov046_020c3500->target, &data_ov046_020c3500->eye, &diff);
        dirCopy = diff;
        VEC_Normalize(&dirCopy, &normalized);
        direction = normalized;
        Camera_BlendToVelocityAim(&direction, 0, 0);
        return;
    }
    view.position = snapshot->position;
    view.direction = snapshot->direction;
    up.x = 0;
    up.y = FX32_ONE;
    up.z = 0;
    view.up = up;
    view.fov = 0x1e000;
    data_ov046_020c3500->followPreset = snapshot->followPreset;
    data_ov046_020c3500->prevPreset = snapshot->followPreset;
    data_ov046_020c3500->blendScale = snapshot->blendScale;
    data_ov046_020c3500->blendSpeed = snapshot->blendSpeed;
    if (data_ov046_020c3500->followPreset == 0x17) {
        data_ov046_020c3500->followPreset = data_ov046_020c3500->prevPreset = 0;
    }
    data_ov046_020c3500->state = snapshot->state;
    if (data_ov046_020c3500->optionFlags & 1) {
        data_ov046_020c3500->state |= 0x10000000;
    } else {
        data_ov046_020c3500->state &= ~0x10000000;
    }
    Camera_BlendToVelocityAim(&view.direction, 0, 0);
}


