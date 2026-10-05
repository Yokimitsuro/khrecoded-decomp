#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 stateFlags;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

void Camera_SetStateFlag18(BOOL enable)
{
    CameraManager *camera = data_ov046_020c3500;

    if (enable) {
        camera->stateFlags |= 0x40000;
        return;
    }
    camera->stateFlags &= ~0x40000;
}
