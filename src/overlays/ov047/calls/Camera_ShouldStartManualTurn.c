#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GameSettings {
    u8 pad_00[0x2878];
    u32 unk0 : 7;
    u32 classicControls : 1;
} GameSettings;

typedef struct CameraManager {
    u8 pad_00[0xdc];
    u32 inputFlags;
} CameraManager;

extern GameSettings *data_0205fe0c;
extern u16 data_020604fc;
extern u16 data_02060500;
extern VecFx32 *func_ov046_020c17a0(void);
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);

BOOL Camera_ShouldStartManualTurn(void *tracking, CameraManager *camera, u32 buttons)
{
    if (func_ov046_020c17a0() != func_ov001_0206dc4c(0)) {
        return FALSE;
    }
    if (!data_0205fe0c->classicControls) {
        if ((data_02060500 & 0x100) && !(buttons & 0x2000) && !(data_02060500 & 0x200)) {
            return TRUE;
        }
    } else if ((camera->inputFlags & 0x100) && !(data_020604fc & 0x100) && !(buttons & 0x2000) &&
               !(data_02060500 & 0x200)) {
        return TRUE;
    }
    return FALSE;
}
