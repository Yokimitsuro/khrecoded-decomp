#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 fov;
} CameraView;

typedef struct CameraState {
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
    fx32 fov;
    u8 pad_28[0xc];
    s32 hasOffset;
    u8 pad_38[8];
    s32 isRaw : 1;
} CameraState;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void CameraPath_TransformKey(void *work, CameraState *state);

void Camera_BuildViewFromState(void *work, CameraState *source, CameraView *out)
{
    VecFx32 dir;
    VecFx32 diff;
    VecFx32 dirCopy;
    CameraState state;

    if (source->isRaw) {
        *out = *(CameraView *)source;
        return;
    }
    state = *source;
    if (source->hasOffset) {
        CameraPath_TransformKey(work, &state);
    }
    out->position = state.position;
    VEC_Subtract(&state.target, &state.position, &diff);
    dirCopy = diff;
    VEC_Normalize(&dirCopy, &dir);
    out->direction = dir;
    out->up = state.up;
    out->fov = state.fov;
}
