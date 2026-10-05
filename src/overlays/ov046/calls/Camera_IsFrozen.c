#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x84];
    u32 flags;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

BOOL Camera_IsFrozen(void)
{
    return (data_ov046_020c3500->flags & 1) != 0;
}
