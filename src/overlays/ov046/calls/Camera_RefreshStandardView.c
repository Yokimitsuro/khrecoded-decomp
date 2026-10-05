#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov047_020c6d44(void);

void Camera_RefreshStandardView(void)
{
    switch (data_ov046_020c3500->type) {
    case 0:
        func_ov047_020c6d44();
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
