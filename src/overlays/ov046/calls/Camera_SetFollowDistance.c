#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x12c];
    fx32 followDistance;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

void Camera_SetFollowDistance(fx32 distance)
{
    data_ov046_020c3500->followDistance = distance;
}
