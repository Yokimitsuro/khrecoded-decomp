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
extern void InitLaunchedParticle(void *motion, const VecFx32 *forward, const VecFx32 *offset, s32 duration, s32 arg4, s32 arg5);

static inline MtxFx33 GetViewRotation(void)
{
    MtxFx33 rotation;
    func_01ff913c(&NNS_G3dGlb_cameraMtx, &rotation);
    return rotation;
}

void Camera_StartViewMotion(const VecFx32 *offset, s32 duration, s32 arg4, s32 arg5)
{
    MtxFx33 rotation = GetViewRotation();
    InitLaunchedParticle(data_ov046_020c3500->motion, (const VecFx32 *)rotation.m[2], offset, duration, arg4, arg5);
}
