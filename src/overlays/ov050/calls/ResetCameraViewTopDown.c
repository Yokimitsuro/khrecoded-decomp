#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 offset;
    VecFx32 up;
    u8 pad24[0x24];
    fx32 followX;
    fx32 followY;
    s32 unk50;
} CameraView;

extern VecFx32 data_0205344c;
extern CameraView *func_ov046_020c0d78(void);

void ResetCameraViewTopDown(void)
{
    CameraView *view = func_ov046_020c0d78();
    VecFx32 offset;
    VecFx32 up;
    view->position = data_0205344c;
    offset.x = 0;
    offset.y = 0;
    offset.z = FX32_ONE;
    view->offset = offset;
    up.x = 0;
    up.y = FX32_ONE;
    up.z = 0;
    view->up = up;
    view->followX = 0x333;
    view->unk50 = 0;
    view->followY = 0x333;
}
