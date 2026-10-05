#include "nitro/types.h"

typedef struct {
    u32 unk_00 : 2;
    u32 invertY : 1;
    u32 cameraMode : 2;
    u32 invertX : 1;
    u32 autoFollow : 1;
} CameraConfig;

typedef struct {
    u8 pad_0000[0x2878];
    CameraConfig config;
} SaveData;

typedef struct {
    u8 _0[0x38];
    u32 flags;
    u32 configFlags;
} CameraState;

extern CameraState *data_ov042_020be5e0;
extern SaveData *data_0205fe0c;

void ApplyCameraConfig(void) {
    CameraState *camera = data_ov042_020be5e0;
    u32 mode;
    camera->flags &= ~0x10000000;
    camera->configFlags = 0;
    if (data_0205fe0c->config.invertY == 1) {
        camera->configFlags |= 1;
        camera->flags |= 0x10000000;
    }
    mode = data_0205fe0c->config.cameraMode;
    if (mode == 0) {
        camera->configFlags |= 2;
    }
    if (mode == 2) {
        camera->configFlags |= 4;
    }
    if (data_0205fe0c->config.invertX == 1) {
        camera->configFlags |= 8;
    }
    if (data_0205fe0c->config.autoFollow == 1) {
        camera->configFlags |= 0x10;
    }
}
