#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 _0[0xc];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 eye;
    VecFx32 target;
    VecFx32 up;
    u32 flags;
    u32 unk_3c;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    fx32 unk_4c;
    fx32 unk_50;
    fx32 unk_54;
    VecFx32 goalTarget;
    VecFx32 goalEye;
    VecFx32 shake;
    VecFx32 eyeOffset;
    VecFx32 liveTarget;
    VecFx32 liveEye;
    u32 unk_a0;
    u32 unk_a4;
    u32 unk_a8;
} CameraState;

typedef void (*CameraUpdateFunc)(void);

extern CameraState *data_ov043_020bd2e0;
extern VecFx32 data_0205344c;
extern void func_ov043_020bd0a8(void);
extern void LoadDefaultProjectionValues(CameraState *camera);
extern VecFx32 *GetSubStruct1C(void);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void func_ov043_020bcce4(void);

CameraUpdateFunc InitCameraState_020bcbec(int unused, CameraState *camera) {
    VecFx32 offset;
    VecFx32 target;
    data_ov043_020bd2e0 = camera;
    camera->flags = 3;
    camera->unk_a0 = 0;
    camera->unk_a4 = 0;
    camera->unk_3c = 0;
    camera->unk_40 = 0;
    camera->unk_44 = 0;
    camera->unk_48 = 0;
    offset.x = 0;
    offset.y = 0x1666;
    offset.z = 0;
    camera->eyeOffset = offset;
    camera->unk_4c = 0x800;
    camera->unk_50 = 0x800;
    camera->unk_54 = 0xccd;
    func_ov043_020bd0a8();
    LoadDefaultProjectionValues(camera);
    camera->eye = camera->eyeOffset;
    camera->goalEye = camera->eye;
    VEC_MultAdd(0x4000, GetSubStruct1C(), &camera->eye, &target);
    camera->target = target;
    camera->goalTarget = camera->target;
    camera->farClip = 0x7d000;
    camera->nearClip = 0x19a;
    camera->liveTarget = camera->goalTarget;
    camera->liveEye = camera->goalEye;
    camera->shake = data_0205344c;
    camera->unk_a8 = 0;
    return func_ov043_020bcce4;
}
