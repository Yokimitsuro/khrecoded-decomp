#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0xe0];
    u32 inputFlags;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern fx32 FX_Mul(fx32 left, fx32 right);

fx32 Camera_GetSpeedScaledStep(void)
{
    CameraManager *camera = data_ov046_020c3500;
    fx32 scale = 0x1000;

    if (camera->inputFlags & 2) {
        scale = 0xa66;
    }
    if (camera->inputFlags & 4) {
        scale = 0x1f33;
    }
    return FX_Mul(0x4cd, scale);
}
