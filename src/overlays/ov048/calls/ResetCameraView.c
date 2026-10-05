#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 offset;
    VecFx32 up;
    s32 angle;
} CameraView;

extern VecFx32 data_0205344c;
extern CameraView *func_ov046_020c0d58(void);

void ResetCameraView(void)
{
    CameraView *view = func_ov046_020c0d58();
    VecFx32 offset;
    VecFx32 up;
    view->position = data_0205344c;
    offset.x = 0;
    offset.y = 0x1333;
    offset.z = 0;
    view->offset = offset;
    up.x = 0;
    up.y = 0;
    up.z = FX32_ONE;
    view->up = up;
    view->angle = 0xb2;
}
