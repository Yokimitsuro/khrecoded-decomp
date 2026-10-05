#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void func_ov047_020c3578(int viewMode, void *out);

void Camera_ChangeViewMode(int viewMode, void *out)
{
    switch (data_ov046_020c3500->type) {
    case 0:
        func_ov047_020c3578(viewMode, out);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
