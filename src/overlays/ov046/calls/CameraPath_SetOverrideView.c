#include "nitro/types.h"

typedef struct CameraOverrideView {
    u32 data[12];
} CameraOverrideView;

typedef struct EventCameraWork {
    u8 pad_00[0x34];
    int pathKind;
    u8 pad_38[0xf0];
    CameraOverrideView directView;
    CameraOverrideView pathView;
    BOOL pathViewSet;
    void *activePath;
} EventCameraWork;

extern s32 func_ov046_020c0d88(void);
extern EventCameraWork *func_ov046_020c0d68(void);

BOOL CameraPath_SetOverrideView(const CameraOverrideView *view)
{
    EventCameraWork *work;

    if (func_ov046_020c0d88() == 2) {
        work = func_ov046_020c0d68();
        if (work->activePath != NULL) {
            if (work->pathKind == 2) {
                work->directView = *view;
            } else {
                work->pathView = *view;
                work->pathViewSet = TRUE;
            }
            return TRUE;
        }
    }
    return FALSE;
}
