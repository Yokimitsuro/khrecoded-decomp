#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
} CameraView;

typedef struct CameraManager {
    u8 pad_00[0x134];
    fx32 viewDistance;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void Camera_GetRaisedPlayerPosition(VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline void NormalizeVec(VecFx32 vec, VecFx32 *out)
{
    VEC_Normalize(&vec, out);
}

void Camera_AimViewAtPlayer(CameraView *view)
{
    CameraManager *camera = data_ov046_020c3500;
    VecFx32 focus;
    VecFx32 direction;
    VecFx32 delta;

    Camera_GetRaisedPlayerPosition(&focus);
    VEC_Subtract(&focus, &view->position, &delta);
    NormalizeVec(delta, &direction);
    view->direction = direction;
    view->up = MakeVec(0, 0x1000, 0);
    VEC_MultAdd(-camera->viewDistance, &view->direction, &focus, &view->position);
}
