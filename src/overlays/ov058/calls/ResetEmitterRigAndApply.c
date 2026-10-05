#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void RebindEmitterSlots(EmitterRig *rig, int blend);
extern void PlaceRigAtPlayerOffset(EmitterRig *rig, int arg);

void ResetEmitterRigAndApply(EmitterRig *rig, int arg)
{
    rig->phase = 1;
    RebindEmitterSlots(rig, 0);
    PlaceRigAtPlayerOffset(rig, arg);
}
