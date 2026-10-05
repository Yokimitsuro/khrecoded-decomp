#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 words[14];
} CameraCutHeader;

typedef struct {
    u8 pad_00[0x18];
    fx32 startY;
    u8 pad_1c[0x24 - 0x1c];
    fx32 endY;
    u8 pad_28[0x3c - 0x28];
    fx32 distance;
    fx32 speed;
    fx32 heightOffset;
} CameraCutPath;

typedef struct {
    u8 pad_00[0x44];
    VecFx32 baseRotation;
    u8 pad_50[0x90 - 0x50];
    s32 timer;
    s32 duration;
    s32 cutId;
    u8 pad_9c[0x19c - 0x9c];
    CameraCutHeader savedPath;
    u8 pad_1d4[0x1dc - 0x1d4];
    u16 active;
    u8 pad_1de[0x1e0 - 0x1de];
    s32 targetOverride;
} EventCameraManager;

extern EventCameraManager *data_ov001_020a0514;
extern int func_02029f5c(void);
extern int abs(int value);
extern void ForwardSubModeEvent(EventCameraManager *manager, int target, CameraCutPath *path);
extern BOOL GetPanelFieldB8(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void ActorChannel_ResetFields(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int Math_AsinIdx(fx32 ratio);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void SetFieldCameraTarget(int actorId, int mode, fx32 speed, int roll, VecFx32 *position, VecFx32 *rotation);

void StartEventCameraCut(void) {
    EventCameraManager *manager = data_ov001_020a0514;
    VecFx32 rotation;
    VecFx32 position;
    CameraCutPath path;
    fx32 ratio;
    int mode;

    if (manager->active == 0 || manager->cutId == -1) {
        return;
    }
    if (abs(func_02029f5c()) == 0x10) {
        return;
    }
    rotation = manager->baseRotation;
    if (manager->targetOverride != -1) {
        rotation.x = manager->targetOverride;
    }
    ForwardSubModeEvent(manager, rotation.x, &path);
    if (manager->cutId == 1 && !GetPanelFieldB8()) {
        MI_CpuCopy8(&path, &manager->savedPath, sizeof(CameraCutHeader));
        ActorChannel_ResetFields();
        manager->duration = 10;
        manager->timer = manager->duration;
        manager->cutId = 6;
        return;
    }
    ratio = FX_Div(path.endY - path.startY, path.distance);
    if (ratio >= -0x1000 && ratio <= 0x1000) {
        rotation.y = -(u16)Math_AsinIdx(ratio);
    }
    mode = 0;
    position = *func_ov001_0206dc4c(0);
    position.y += path.heightOffset;
    if (!GetPanelFieldB8()) {
        mode = 10;
    }
    SetFieldCameraTarget(-1, mode, path.speed, 0x1554, &position, &rotation);
    if (manager->cutId == 1) {
        ActorChannel_ResetFields();
    }
    manager->cutId = 5;
}
