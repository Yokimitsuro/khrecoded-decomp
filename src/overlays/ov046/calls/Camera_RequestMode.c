#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
    u8 pad_84[0x60];
    int mode;
    int previousMode;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov047_020c36e8(int mode, int arg);

void Camera_RequestMode(int mode, int arg)
{
    if (data_ov046_020c3500->type != 0) {
        data_ov046_020c3500->previousMode = data_ov046_020c3500->mode;
        data_ov046_020c3500->mode = mode;
    } else {
        func_ov047_020c36e8(mode, arg);
    }
}
