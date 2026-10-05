#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 offset;
    VecFx32 up;
    s32 angle;
} CameraView;

extern CameraView *func_ov046_020c0d58(void);

VecFx32 *GetCameraViewUpVector(void)
{
    return &func_ov046_020c0d58()->up;
}
