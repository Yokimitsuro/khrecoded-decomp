#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x130];
    fx32 heightOffset;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);

void Camera_GetRaisedPlayerPosition(VecFx32 *out)
{
    CameraManager *camera = data_ov046_020c3500;
    VecFx32 *position = func_ov001_0206dc4c(0);
    VecFx32 result;

    result.x = position->x;
    result.y = position->y + camera->heightOffset;
    result.z = position->z;
    *out = result;
}
