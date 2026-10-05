#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern BOOL func_ov047_020c6ba4(void);

BOOL Camera_HasPendingModeChange(void)
{
    switch (data_ov046_020c3500->type) {
    case 0:
        return func_ov047_020c6ba4();
    case 1:
    case 2:
    case 3:
        break;
    }
    return FALSE;
}
