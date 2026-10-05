#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraManager {
    u8 pad_00[0x88];
    u8 motion[0x48];
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern MtxFx43 NNS_G3dGlb_cameraMtx;
extern void func_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern void InitDriftParticle(void *particle, const VecFx32 *position, int param30, int param2c);

static inline MtxFx33 GetViewRotation(void)
{
    MtxFx33 rotation;
    func_01ff913c(&NNS_G3dGlb_cameraMtx, &rotation);
    return rotation;
}

void Camera_StartDriftAlongView(int param30, int param2c)
{
    MtxFx33 rotation = GetViewRotation();
    InitDriftParticle(data_ov046_020c3500->motion, (const VecFx32 *)rotation.m[2], param30, param2c);
}
