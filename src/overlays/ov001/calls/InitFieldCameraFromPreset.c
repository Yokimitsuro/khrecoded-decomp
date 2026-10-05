#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 heading;
    u8 pad_04[8];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    u8 pad_2c[0xc];
} CameraView;

typedef struct {
    CameraView view;
    s32 pitch;
    fx32 distance;
    u8 pad_40[8];
} CameraPreset;

typedef struct {
    CameraView view;
    VecFx32 anchor;
    s32 pitch;
    s32 elevation;
    s32 roll;
    u8 pad_50[0x30];
    fx32 distance;
    s32 headingAngle;
    u8 pad_88[8];
    s32 followMode;
    u8 pad_94[4];
    s32 followTargetA;
    s32 followTargetB;
    u8 pad_a0[0x134];
    void *message;
    void *loader;
    u16 loading;
    u8 pad_1de[2];
    s32 pendingId;
} FieldCamera;

extern FieldCamera *data_ov001_020a0514;
extern char sOv001_EvEcamP2_0209f338[];
extern BOOL GetManagerUnknownValue(void);
extern void CopySubModeState(CameraPreset *preset);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int Math_AsinIdx(fx32 value);
extern void ResetFieldCamera(void);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void Obj_SetWord14(void *loader, void *callback);
extern void UpdateFieldCamera(void);

void InitFieldCameraFromPreset(void)
{
    FieldCamera *camera = data_ov001_020a0514;
    CameraPreset preset;
    fx32 slope;

    if (GetManagerUnknownValue()) {
        CopySubModeState(&preset);
        camera->view = preset.view;
        camera->pitch = preset.pitch;
        camera->distance = preset.distance;
        if (camera->pitch >= 0x7ff8) {
            camera->pitch -= 0xfff0;
        }
        camera->anchor = camera->view.position;
        slope = FX_Div(camera->view.target.y - camera->view.position.y, camera->distance);
        if (slope >= -0x1000 && slope <= 0x1000) {
            camera->elevation = -(u16)Math_AsinIdx(slope);
        }
        camera->roll = 0;
        camera->headingAngle = Math_AsinIdx(camera->view.heading);
        camera->followTargetB = -1;
        camera->followTargetA = -1;
        camera->followMode = 0;
    } else {
        ResetFieldCamera();
    }
    camera->pendingId = -1;
    camera->message = Msg_OpenContainerAndReadHeader(sOv001_EvEcamP2_0209f338, 0xd, FALSE);
    camera->loading = 1;
    Obj_SetWord14(camera->loader, UpdateFieldCamera);
}

