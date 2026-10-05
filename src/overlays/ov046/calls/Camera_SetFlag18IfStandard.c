#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov046_020c2aa4(BOOL enable);

void Camera_SetFlag18IfStandard(BOOL enable)
{
    switch (data_ov046_020c3500->type) {
    case 0:
        func_ov046_020c2aa4(enable);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
