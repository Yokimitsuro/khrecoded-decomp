#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2e0;
extern void RotateCameraUp(s32 angle);

void ResetCameraUp(s32 angle) {
    VecFx32 up;
    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    *(VecFx32 *)(data_ov043_020bd2e0 + 0x2c) = up;
    RotateCameraUp(angle);
}
