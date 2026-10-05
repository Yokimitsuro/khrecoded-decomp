#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x12c];
    fx32 followDistance;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Camera_ComputeHeadingOffset(void *offsetSource, s32 unused, VecFx32 *out);

void Camera_ComputeFollowPoint(void *offsetSource, s32 unused, const VecFx32 *direction,
                                        VecFx32 *out)
{
    CameraManager *camera = data_ov046_020c3500;
    VecFx32 offset;

    VEC_MultAdd(camera->followDistance, direction, func_ov001_0206dc4c(0), out);
    Camera_ComputeHeadingOffset(offsetSource, unused, &offset);
    VEC_Add(out, &offset, out);
}
