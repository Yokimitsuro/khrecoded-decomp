#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraMotion {
    VecFx32 position;
    VecFx32 velocity;
} CameraMotion;

extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void func_ov046_020c17bc(CameraMotion *motion, u16 heading);

void Camera_AimAlongVelocity(CameraMotion *motion)
{
    func_ov046_020c17bc(motion, FX_Atan2Idx(motion->velocity.z, motion->velocity.x));
}
