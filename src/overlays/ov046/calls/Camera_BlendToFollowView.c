#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    u8 pad_0C[0x1c];
} CameraView;

typedef void (*CameraViewBuilder)(CameraView *view);

extern void func_ov046_020c196c(CameraView *view);
extern void func_ov046_020c10f4(s32 returnMode, CameraView *view, s32 curveType, fx32 duration,
                                CameraViewBuilder builder);

void Camera_BlendToFollowView(s32 curveType, fx32 duration)
{
    CameraView view;

    func_ov046_020c196c(&view);
    func_ov046_020c10f4(0, &view, curveType, duration, func_ov046_020c196c);
}
