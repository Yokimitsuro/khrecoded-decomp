#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void RebindEmitterSlots(EmitterRig *rig, int blend);

void RebindEmitterSlotsPhase3(EmitterRig *rig)
{
    rig->phase = 3;
    RebindEmitterSlots(rig, 2);
}
