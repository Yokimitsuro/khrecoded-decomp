#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x2c];
    VecFx32 defaultDirection;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void GetParticleDriftDirection(CameraManager *camera, VecFx32 *out);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);

u16 Camera_GetDriftHeading(void)
{
    VecFx32 direction;
    fx32 height;

    GetParticleDriftDirection(data_ov046_020c3500, &direction);
    height = direction.y;
    if (height < 0) {
        height = -height;
    }
    if (height < data_ov046_020c3500->defaultDirection.y) {
        return FX_Atan2Idx(-direction.x, -direction.z);
    }
    return FX_Atan2Idx(-data_ov046_020c3500->defaultDirection.x, -data_ov046_020c3500->defaultDirection.z);
}
