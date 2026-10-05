#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xec];
    u32 previousSettingFlags;
    u32 settingFlags;
} CameraManager;

extern CameraManager *data_ov046_020c3500;

BOOL Camera_IsFlag3JustSet(void)
{
    if ((data_ov046_020c3500->settingFlags & 8) != 0 &&
        (data_ov046_020c3500->previousSettingFlags & 8) == 0) {
        return TRUE;
    }
    return FALSE;
}
