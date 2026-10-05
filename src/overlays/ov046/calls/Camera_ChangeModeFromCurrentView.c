#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    u8 pad_0C[0x1c];
} CameraView;

typedef struct CameraManager CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov021_020af9fc(CameraManager *camera, CameraView *view);
extern void func_ov046_020c1058(s32 mode, CameraView *view);

void Camera_ChangeModeFromCurrentView(s32 mode)
{
    CameraView view;

    func_ov021_020af9fc(data_ov046_020c3500, &view);
    func_ov046_020c1058(mode, &view);
}
