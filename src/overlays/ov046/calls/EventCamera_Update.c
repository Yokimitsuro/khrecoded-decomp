#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    u8 pad_0C[0x1c];
} CameraView;

typedef struct EventCameraWork {
    u8 pad_00[0x120];
    s32 returnMode;
} EventCameraWork;

extern BOOL func_ov049_020c379c(EventCameraWork *work);
extern void Camera_BuildViewFromState(EventCameraWork *work, EventCameraWork *source, CameraView *view);
extern void Camera_SetViewMode(s32 mode, CameraView *view);

void *EventCamera_Update(EventCameraWork *work)
{
    CameraView view;

    if (func_ov049_020c379c(work)) {
        Camera_BuildViewFromState(work, work, &view);
        Camera_SetViewMode(work->returnMode, &view);
    }
    return NULL;
}
