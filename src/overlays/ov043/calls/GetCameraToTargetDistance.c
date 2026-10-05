#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 perspectiveParams[4];
    fx32 farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
    u32 flags;
} CamActor;

extern CamActor *data_ov043_020bd2e0;
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

fx32 GetCameraToTargetDistance(void)
{
    CamActor *camera = data_ov043_020bd2e0;
    return VEC_Distance(&camera->pos, &camera->target);
}
