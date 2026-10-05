#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 settingFlags;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

BOOL Camera_IsFlag19Set(void)
{
    if (data_ov046_020c3500->settingFlags & 0x80000) {
        return TRUE;
    }
    return FALSE;
}
