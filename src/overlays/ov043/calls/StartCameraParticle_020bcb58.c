#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern u8 *data_ov043_020bd2e0;
extern MtxFx43 NNS_G3dGlb_cameraMtx;
extern void func_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern void InitLaunchedParticle(void *particle, const VecFx32 *position, const VecFx32 *launch, int param40, int param44, int param2c);

void StartCameraParticle_020bcb58(const VecFx32 *launch, int param40, int param44, int param2c) {
    MtxFx33 rotation;
    MtxFx33 fetched;
    func_01ff913c(&NNS_G3dGlb_cameraMtx, &fetched);
    rotation = fetched;
    InitLaunchedParticle(data_ov043_020bd2e0 + 0xa8, (const VecFx32 *)rotation.m[2], launch, param40, param44, param2c);
}
