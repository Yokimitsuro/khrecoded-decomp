#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 side;
    VecFx32 up;
    VecFx32 back;
    VecFx32 focus;
} CameraView;

extern void Camera_GetPlayerBackDirection(VecFx32 *out);
extern VecFx32 *Camera_GetFocusPosition(void);

void Camera_BuildSideView(CameraView *view)
{
    fx32 depth;

    Camera_GetPlayerBackDirection(&view->back);
    view->up.x = 0;
    view->up.z = 0;
    view->up.y = 0x1000;
    view->side = view->back;
    depth = view->side.x;
    view->side.x = view->side.z;
    view->side.z = depth;
    view->side.x *= -1;
    view->focus = *Camera_GetFocusPosition();
}
