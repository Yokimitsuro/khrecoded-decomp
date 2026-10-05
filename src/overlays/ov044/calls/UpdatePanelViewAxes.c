#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 sideOffset;
    fx32 aspect;
    fx32 tanHalf;
    u8 pad0c[0x100];
    int fieldOfView;
    u8 pad110[0x54];
    VecFx32 upAxis;
    VecFx32 sideAxis;
    VecFx32 rotatedUp;
    VecFx32 reflectedUp;
} Panel;

extern Panel *data_ov044_020d0ec0;
extern MtxFx43 NNS_G3dGlb_cameraMtx;

extern void func_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *axis, fx32 angle);
extern VecFx32 ReflectVectorAcrossNormal(const VecFx32 *vec, const VecFx32 *normal);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void UpdatePanelViewAxes(void)
{
    Panel *panel = data_ov044_020d0ec0;
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
    angle = panel->fieldOfView / 2;
    up = *(VecFx32 *)view.m[1];
    RotateVecTowardVec(&up, (VecFx32 *)view.m[2], angle);
    panel->rotatedUp = up;
    reflectedUp = ReflectVectorAcrossNormal(&panel->rotatedUp, (VecFx32 *)view.m[2]);
    panel->reflectedUp = reflectedUp;
    scale = FX_Div(0x1000, panel->tanHalf);
    scale = (fx32)(((s64)panel->aspect * scale + 0x800) >> 12);
    side = *(VecFx32 *)view.m[0];
    ScaleVecFx32InPlace(&side, scale);
    panel->sideAxis = side;
    VEC_MultAdd(panel->sideOffset, (VecFx32 *)view.m[2], &panel->sideAxis, &sum);
    panel->sideAxis = sum;
    VEC_Normalize(&panel->sideAxis, &panel->sideAxis);
    upAxis = ReflectVectorAcrossNormal(&panel->sideAxis, (VecFx32 *)view.m[2]);
    panel->upAxis = upAxis;
}



