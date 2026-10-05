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
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void SetSoundListenerFrame(VecFx32 *pos, VecFx32 *dir, VecFx32 *up);
extern void func_ov043_020bc840(CamActor *camera);

void UpdateCameraBasisAndCommit(int updateBasis)
{
    CamActor *camera = data_ov043_020bd2e0;

    if ((camera->flags & 4) == 0) {
        if (updateBasis != 0) {
            VecFx32 direction;
            VEC_Subtract(&camera->target, &camera->pos, &direction);
            SetSoundListenerFrame(&camera->pos, &direction, &camera->up);
        }
        func_ov043_020bc840(camera);
    }
}
