#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPose {
    fx32 angleX;
    fx32 angleY;
    u8 pad_08[0xc];
    VecFx32 target;
    VecFx32 position;
    VecFx32 up;
} CameraPose;

typedef struct FieldCamera {
    CameraPose pose;
    u8 pad_38[0x98 - 0x38];
    s32 mode;
    u8 pad_9c[0x140 - 0x9c];
    u8 anim[0x10];
    CameraPose altPose;
    u8 pad_188[0x1e4 - 0x188];
    s32 animActive;
} FieldCamera;

extern FieldCamera *data_ov001_020a0514;

extern void UpdateEventCameraTransform(void);
extern void func_ov001_0208b5d0(void);
extern void func_ov001_0208b6ec(void);
extern void InterpolateFieldCamera(int a, int b, int c, int d);
extern void DispatchModeUpdate(CameraPose *pose);
extern void CamAnim_EvalDelta(void *anim, CameraPose *delta);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetSoundListenerFrame(const VecFx32 *position, const VecFx32 *forward, const VecFx32 *up);

int UpdateFieldCamera(void)
{
    CameraPose current;
    VecFx32 forward;
    CameraPose delta;
    CameraPose pose;
    FieldCamera *camera = data_ov001_020a0514;

    switch (camera->mode) {
    case -1:
        return 0;
    case 0:
        DispatchModeUpdate(&camera->pose);
        MI_CpuCopy8(&camera->pose, &current, sizeof(CameraPose));
        goto apply;
    case 1:
        UpdateEventCameraTransform();
        MI_CpuCopy8(&camera->altPose, &current, sizeof(CameraPose));
        goto apply;
    case 6:
        func_ov001_0208b5d0();
        goto useBase;
    case 7:
        func_ov001_0208b6ec();
        goto useBase;
    default:
        InterpolateFieldCamera(0, 0, 0, 0);
        if (camera->animActive != 0) {
            goto animate;
        }
    useBase:
        DispatchModeUpdate(&camera->pose);
        MI_CpuCopy8(&camera->pose, &current, sizeof(CameraPose));
        goto apply;
    animate:
        CamAnim_EvalDelta(camera->anim, &delta);
        MI_CpuCopy8(&camera->pose, &pose, sizeof(CameraPose));
        VEC_Add(&camera->pose.position, &delta.position, &pose.position);
        VEC_Add(&camera->pose.target, &delta.target, &pose.target);
        VEC_Add(&camera->pose.up, &delta.up, &pose.up);
        pose.angleX += delta.angleX;
        pose.angleY += delta.angleY;
        DispatchModeUpdate(&pose);
        MI_CpuCopy8(&pose, &current, sizeof(CameraPose));
        break;
    }
apply:
    VEC_Subtract(&current.target, &current.position, &forward);
    SetSoundListenerFrame(&current.position, &forward, &current.up);
    return 0;
}
