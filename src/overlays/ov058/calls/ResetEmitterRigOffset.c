#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 offset;
    u8 pad_0b0[0x130 - 0xb0];
    s32 phase;
} EmitterRig;

extern const VecFx32 data_ov058_020d8a4c;

extern void func_ov058_020d74b8(EmitterRig *rig, int blend);

void ResetEmitterRigOffset(EmitterRig *rig)
{
    rig->phase = 1;
    func_ov058_020d74b8(rig, 0);
    rig->offset = data_ov058_020d8a4c;
}
