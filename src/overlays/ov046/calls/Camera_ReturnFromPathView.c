#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPath {
    void *nodes;
    u16 nodeCount;
    u8 pad_06[0x46];
    s32 curveType;
    fx32 duration;
} CameraPath;

typedef struct EventCameraWork {
    u8 pad_00[0x18c];
    CameraPath *activePath;
} EventCameraWork;

extern s32 func_ov046_020c0d88(void);
extern EventCameraWork *func_ov046_020c0d68(void);
extern void Camera_BlendToFollowView(s32 curveType, fx32 duration);

BOOL Camera_ReturnFromPathView(void)
{
    CameraPath *path;

    if (func_ov046_020c0d88() == 2) {
        path = func_ov046_020c0d68()->activePath;
        if (path != NULL) {
            Camera_BlendToFollowView(path->curveType, path->duration);
            return TRUE;
        }
    }
    return FALSE;
}
