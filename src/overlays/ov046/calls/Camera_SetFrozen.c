#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x84];
    u32 flags;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

void Camera_SetFrozen(BOOL frozen)
{
    if (frozen) {
        data_ov046_020c3500->flags |= 1;
        return;
    }
    data_ov046_020c3500->flags &= ~1;
}
