#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xe0];
    u32 optionFlags;
    u8 pad_e4[0xf0 - 0xe4];
    u32 stateFlags;
} CameraManager;

typedef struct GameSettings {
    u8 pad_00[0x2878];
    u32 unk0 : 2;
    u32 invertCamera : 1;
    u32 cameraSpeed : 2;
    u32 invertX : 1;
    u32 invertY : 1;
} GameSettings;

extern CameraManager *data_ov046_020c3500;
extern GameSettings *data_0205fe0c;

void Camera_LoadOptionFlags(void)
{
    CameraManager *camera = data_ov046_020c3500;
    u32 speed;

    camera->stateFlags &= ~0x10000000;
    camera->optionFlags = 0;
    if (data_0205fe0c->invertCamera == 1) {
        camera->optionFlags |= 1;
        camera->stateFlags |= 0x10000000;
    }
    speed = data_0205fe0c->cameraSpeed;
    if (speed == 0) {
        camera->optionFlags |= 2;
    }
    if (speed == 2) {
        camera->optionFlags |= 4;
    }
    if (data_0205fe0c->invertX == 1) {
        camera->optionFlags |= 8;
    }
    if (data_0205fe0c->invertY == 1) {
        camera->optionFlags |= 0x10;
    }
}
