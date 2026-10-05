#include "nitro/types.h"

typedef struct {
    u8 _0[0x38];
    u32 flags;
} CameraState;

extern CameraState *data_ov043_020bd2e0;

void SetCameraFlag4(BOOL enable) {
    CameraState *camera = data_ov043_020bd2e0;
    u32 flags;
    if (enable) {
        flags = camera->flags | 4;
    } else {
        flags = camera->flags & ~4;
    }
    camera->flags = flags;
}
