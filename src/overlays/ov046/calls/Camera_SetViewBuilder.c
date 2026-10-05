#include "nitro/types.h"

typedef struct CameraView CameraView;
typedef void (*CameraViewBuilder)(CameraView *view);

typedef struct CameraManager {
    u8 pad_00[0x260];
    CameraViewBuilder viewBuilder;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

void Camera_SetViewBuilder(CameraViewBuilder builder)
{
    data_ov046_020c3500->viewBuilder = builder;
}
