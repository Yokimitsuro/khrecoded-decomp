#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void func_ov058_020d74b8(EmitterRig *rig, int blend);

void RebindEmitterSlotsPhase3_020d7784(EmitterRig *rig)
{
    rig->phase = 3;
    func_ov058_020d74b8(rig, 2);
}
