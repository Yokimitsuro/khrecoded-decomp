#include "nitro/types.h"

typedef struct FollowControl {
    u8 pad_00[0x94];
    s32 distance;
    s32 blendTimer;
    s32 height;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0xe4];
    s32 followPreset;
    u8 pad_e8[0xf0 - 0xe8];
    u32 stateFlags;
    u8 pad_f4[0x138 - 0xf4];
    void *controller;
    u8 controllerData[4];
} CameraManager;

typedef struct GameSettings {
    u8 pad_00[0x2878];
    u32 unk0 : 2;
    u32 invertCamera : 1;
} GameSettings;

extern CameraManager *data_ov046_020c3500;
extern GameSettings *data_0205fe0c;
extern u32 func_ov046_020c2ad8(CameraManager *camera);
extern s32 func_ov046_020c0d88(void);
extern s32 Camera_ComputeFollowDistance(s32 preset);
extern s32 func_ov046_020c1a68(s32 preset);
extern void Camera_SetStateFlag18(BOOL enable);

void Camera_SetFollowSuspended(BOOL suspended)
{
    CameraManager *camera = data_ov046_020c3500;

    if (!suspended) {
        if (data_0205fe0c->invertCamera == 1) {
            camera->stateFlags |= 0x10000000;
        }
        if (func_ov046_020c2ad8(camera)) {
            if (func_ov046_020c0d88() == 0) {
                ((FollowControl *)data_ov046_020c3500->controllerData)->blendTimer = 0;
            }
            if (camera->stateFlags & 0x80000) {
                camera->stateFlags &= ~0x80000;
                if (func_ov046_020c0d88() == 0) {
                    FollowControl *follow = (FollowControl *)data_ov046_020c3500->controllerData;
                    follow->distance = Camera_ComputeFollowDistance(camera->followPreset);
                    follow->height = func_ov046_020c1a68(camera->followPreset);
                }
            }
        }
    } else {
        camera->stateFlags &= ~0x10000000;
    }
    Camera_SetStateFlag18(suspended);
}




