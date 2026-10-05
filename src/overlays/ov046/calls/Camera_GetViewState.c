#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraBaseParams {
    u8 pad_00[0x14];
    VecFx32 position;
    u8 pad_20[0x18];
} CameraBaseParams;

typedef struct CameraManager {
    CameraBaseParams base;
    VecFx32 eye;
    VecFx32 target;
    u8 pad_50[0x30];
    int type;
} CameraManager;

typedef struct CameraViewState {
    CameraBaseParams base;
    u32 angle;
    fx32 distance;
} CameraViewState;

extern CameraManager *data_ov046_020c3500;
extern void func_ov047_020c6bc4(CameraViewState *state);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

void Camera_GetViewState(CameraViewState *state)
{
    CameraManager *camera = data_ov046_020c3500;

    switch (camera->type) {
    case 0:
        func_ov047_020c6bc4(state);
        break;
    case 1:
    case 2:
    case 3:
        state->base = camera->base;
        state->base.position = camera->target;
        state->angle = FX_Atan2Idx(camera->eye.x - camera->target.x, camera->eye.z - camera->target.z);
        state->distance = VEC_Distance(&data_ov046_020c3500->eye, &data_ov046_020c3500->target);
        break;
    }
}
