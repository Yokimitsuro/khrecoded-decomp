#include "nitro/types.h"

typedef struct {
    u8 _0[0x40];
    int mode;
} CameraState;

extern CameraState *data_ov043_020bd2e0;

void SetCameraModeValue(int mode) {
    CameraState *camera = data_ov043_020bd2e0;
    if (camera->mode != mode) {
        camera->mode = mode;
    }
}
