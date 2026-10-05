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
extern void func_ov046_020c2df0(EventCameraWork *work, EventCameraWork *source, CameraView *view);
extern void func_ov046_020c1058(s32 mode, CameraView *view);

void *EventCamera_Update(EventCameraWork *work)
{
    CameraView view;

    if (func_ov049_020c379c(work)) {
        func_ov046_020c2df0(work, work, &view);
        func_ov046_020c1058(work->returnMode, &view);
    }
    return NULL;
}
