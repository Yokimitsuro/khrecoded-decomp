#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5e0;
extern u32 func_ov030_020bb374(void);
extern void InitLaunchedParticle(void *particle, const VecFx32 *position, const VecFx32 *launch, int param40, int param44, int param2c);

void StartCameraParticle(const VecFx32 *launch, int param40, int param44, int param2c) {
    *(u32 *)(data_ov042_020be5e0 + 0x38) &= ~0x10000;
    *(u32 *)(data_ov042_020be5e0 + 0x38) |= 0x8000;
    InitLaunchedParticle(data_ov042_020be5e0 + 0x148, (const VecFx32 *)func_ov030_020bb374(), launch, param40, param44, param2c);
}
