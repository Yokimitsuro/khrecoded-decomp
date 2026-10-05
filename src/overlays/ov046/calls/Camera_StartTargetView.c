#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov047_020c6c00(void *target, u32 angle, void *out);

void Camera_StartTargetView(void *target, u32 angle, void *out)
{
    switch (data_ov046_020c3500->type) {
    case 0:
        func_ov047_020c6c00(target, angle, out);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
