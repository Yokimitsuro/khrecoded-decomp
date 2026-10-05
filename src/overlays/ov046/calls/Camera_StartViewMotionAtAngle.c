#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 func_ov021_020af8f4(s32 angle);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void Camera_StartViewMotion(const VecFx32 *offset, s32 duration, s32 arg4, s32 arg5);

static inline VecFx32 Scaled(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace(&vec, scale);
    return vec;
}

void Camera_StartViewMotionAtAngle(s32 angle, fx32 distance, s32 duration, s32 arg4, s32 arg5)
{
    VecFx32 offset = Scaled(func_ov021_020af8f4(angle), distance);
    Camera_StartViewMotion(&offset, duration, arg4, arg5);
}
