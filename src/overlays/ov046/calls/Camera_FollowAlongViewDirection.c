#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
} CameraView;

extern void func_ov046_020c2c18(const VecFx32 *direction, VecFx32 *out);

void Camera_FollowAlongViewDirection(CameraView *view)
{
    func_ov046_020c2c18(&view->direction, &view->position);
}
