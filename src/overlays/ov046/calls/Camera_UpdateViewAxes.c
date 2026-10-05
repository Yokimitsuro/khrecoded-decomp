#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraManager {
    fx32 sideOffset;
    fx32 aspect;
    fx32 tanHalf;
    u8 pad_0c[0x50 - 0x0c];
    VecFx32 upAxis;
    VecFx32 sideAxis;
    VecFx32 rotatedUp;
    VecFx32 reflectedUp;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern MtxFx43 NNS_G3dGlb_cameraMtx;

extern void func_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern u16 Math_AsinIdx(int sine);
extern void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *axis, fx32 angle);
extern VecFx32 ReflectVectorAcrossNormal(const VecFx32 *vec, const VecFx32 *normal);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int FX_Mul(int left, int right);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void Camera_UpdateViewAxes(void)
{
    CameraManager *camera = data_ov046_020c3500;
    MtxFx33 view;
    VecFx32 reflectedUp;
    VecFx32 upAxis;
    MtxFx33 fetched;
    VecFx32 up;
    VecFx32 side;
    VecFx32 sum;
    fx32 scale;
    fx32 angle;

    func_01ff913c(&NNS_G3dGlb_cameraMtx, &fetched);
    view = fetched;
    angle = (fx32)((s64)Math_AsinIdx(camera->sideOffset) * 0x6488 / 0x10000);
    up = *(VecFx32 *)view.m[1];
    RotateVecTowardVec(&up, (VecFx32 *)view.m[2], angle);
    data_ov046_020c3500->rotatedUp = up;
    reflectedUp = ReflectVectorAcrossNormal(&data_ov046_020c3500->rotatedUp, (VecFx32 *)view.m[2]);
    data_ov046_020c3500->reflectedUp = reflectedUp;
    scale = FX_Div(0x1000, camera->tanHalf);
    scale = FX_Mul(camera->aspect, scale);
    side = *(VecFx32 *)view.m[0];
    ScaleVecFx32InPlace(&side, scale);
    data_ov046_020c3500->sideAxis = side;
    VEC_MultAdd(camera->sideOffset, (VecFx32 *)view.m[2], &data_ov046_020c3500->sideAxis, &sum);
    data_ov046_020c3500->sideAxis = sum;
    VEC_Normalize(&data_ov046_020c3500->sideAxis, &data_ov046_020c3500->sideAxis);
    upAxis = ReflectVectorAcrossNormal(&data_ov046_020c3500->sideAxis, (VecFx32 *)view.m[2]);
    data_ov046_020c3500->upAxis = upAxis;
}

