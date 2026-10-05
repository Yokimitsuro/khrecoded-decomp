#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void PlaceRigAtPlayerOffset(EmitterRig *rig, int index);
extern u16 AdvanceAnimationTracks(EmitterRig *rig, fx32 step);
extern void RebindEmitterSlots(EmitterRig *rig, int blend);
extern void func_ov058_020d7a64(int index);

void UpdateHazardRig(EmitterRig *rig, int index, fx32 step)
{
    s32 phase = rig->phase;

    if (phase == 0) {
        return;
    }
    switch (phase) {
    case 1:
        PlaceRigAtPlayerOffset(rig, index);
        if (AdvanceAnimationTracks(rig, step)) {
            RebindEmitterSlots(rig, 1);
            rig->phase = 2;
        }
        break;
    case 2:
        PlaceRigAtPlayerOffset(rig, index);
        AdvanceAnimationTracks(rig, step);
        func_ov058_020d7a64(index);
        break;
    case 3:
        if (AdvanceAnimationTracks(rig, step)) {
            rig->phase = 0;
        }
        break;
    }
}
