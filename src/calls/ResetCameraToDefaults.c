#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalState {
    u32 unk_00;
    u32 unk_04;
    MtxFx44 projectionMtx;
    u32 unk_48;
    MtxFx43 cameraMtx;
    u8 pad_7C[0x58];
    u32 flags;
} G3dGlobalState;

typedef struct CameraVectors {
    VecFx32 position;
    VecFx32 up;
    VecFx32 target;
} CameraVectors;

typedef struct CameraDefaults {
    VecFx32 target;
    VecFx32 position;
    VecFx32 up;
    MtxFx44 projectionMtx;
} CameraDefaults;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx);

extern G3dGlobalState NNS_G3dGlb;
extern CameraDefaults data_0205fe28;
extern CameraVectors NNS_G3dGlb_camPos;

int ResetCameraToDefaults(void)
{
    MIi_CpuCopyFast(&data_0205fe28.projectionMtx, &NNS_G3dGlb.projectionMtx, sizeof(MtxFx44));
    NNS_G3dGlb.flags &= ~0x50;
    NNS_G3dGlb_camPos.position = data_0205fe28.position;
    NNS_G3dGlb_camPos.up = data_0205fe28.up;
    NNS_G3dGlb_camPos.target = data_0205fe28.target;
    func_01ff9b70(&data_0205fe28.position, &data_0205fe28.up, &data_0205fe28.target, &NNS_G3dGlb.cameraMtx);
    NNS_G3dGlb.flags &= ~0xe8;
    return 0;
}
