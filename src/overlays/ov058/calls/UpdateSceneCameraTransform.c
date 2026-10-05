#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[8];
    VecFx32 center;
    VecFx32 prevCenter;
} SceneCenterState;

extern SceneCenterState data_ov058_020d8a44;
extern s16 data_02053580[];

extern u16 func_ov046_020c3094(void);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_01ff9110(const MtxFx33 *src, MtxFx43 *dst);
extern void CameraPath_SetOverrideView(MtxFx43 *mtx);

void UpdateSceneCameraTransform(BOOL force)
{
    SceneCenterState *state = &data_ov058_020d8a44;
    BOOL changed = TRUE;
    int index;
    MtxFx43 mtx;
    MtxFx33 rot;

    if (!force && state->center.x == state->prevCenter.x && state->center.y == state->prevCenter.y && state->center.z == state->prevCenter.z) {
        changed = FALSE;
    }
    if (!changed) {
        return;
    }
    index = func_ov046_020c3094() >> 4;
    MTX_RotY33_(&rot, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
    func_01ff9110(&rot, &mtx);
    mtx._30 = state->center.x;
    mtx._31 = state->center.y;
    mtx._32 = state->center.z;
    CameraPath_SetOverrideView(&mtx);
}
