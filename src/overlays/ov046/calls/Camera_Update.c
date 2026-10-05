#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x14];
    VecFx32 eye;
    VecFx32 target;
    VecFx32 up;
    u8 pad_38[0x48];
    int type;
    u8 pad_84[0x04];
    int driftState;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern BOOL Camera_IsFrozen(void);
extern BOOL UpdateDriftParticle(int *particle);
extern void Camera_ApplyOffsetClampHeight(void);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetSoundListenerFrame(const VecFx32 *position, const VecFx32 *forward, const VecFx32 *up);
extern void func_ov046_020c0b54(void *camera);
extern void func_ov047_020c353c(BOOL updateListener);

void Camera_Update(BOOL updateListener)
{
    CameraManager *camera = data_ov046_020c3500;
    VecFx32 forward;

    if (Camera_IsFrozen()) {
        return;
    }
    if (data_ov046_020c3500->driftState != 0) {
        UpdateDriftParticle(&data_ov046_020c3500->driftState);
    }
    Camera_ApplyOffsetClampHeight();
    if (updateListener) {
        VEC_Subtract(&camera->eye, &camera->target, &forward);
        SetSoundListenerFrame(&camera->target, &forward, &camera->up);
    }
    func_ov046_020c0b54(data_ov046_020c3500);
    switch (data_ov046_020c3500->type) {
    case 0:
        func_ov047_020c353c(updateListener);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
