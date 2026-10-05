#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0xf4];
    VecFx32 *focusTarget;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);

VecFx32 *Camera_GetFocusPosition(void)
{
    VecFx32 *focus = data_ov046_020c3500->focusTarget;

    if (focus == NULL) {
        focus = func_ov001_0206dc4c(0);
    }
    return focus;
}
