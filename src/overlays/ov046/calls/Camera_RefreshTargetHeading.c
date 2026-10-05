#include "nitro/types.h"

typedef struct CameraModeState {
    int mode;
    u8 pad_04[0x94];
    int targetHeading;
} CameraModeState;

typedef struct CameraManager {
    u8 pad_00[0xf4];
    int pathActive;
    u8 pad_f8[0x44];
    CameraModeState modeState;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern int func_ov046_020c0d88(void);
extern unsigned int func_ov046_020c2ad8(CameraManager *camera);
extern u16 GetBiasAdjustedField(int playerIndex);

void Camera_RefreshTargetHeading(void)
{
    CameraManager *camera = data_ov046_020c3500;

    camera->pathActive = 0;
    if (func_ov046_020c0d88() == 0) {
        CameraModeState *state = &data_ov046_020c3500->modeState;

        if (!func_ov046_020c2ad8(camera)) {
            state->targetHeading = GetBiasAdjustedField(0);
            return;
        }
        state->targetHeading = 0;
    }
}
