#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    s32 rate;
    u8 pad_18[0xd];
    u8 loop;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct EffectResources {
    u8 pad_00[0xb6];
    s16 trailGroup;
} EffectResources;

typedef struct EffectOwner {
    u8 pad_00[0x10];
    s32 effectSlot;
} EffectOwner;

extern EffectResources *data_ov001_020a04bc;

extern void ResetAnimationTrackState(TrackState *state);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern int func_ov021_020a8cc0(TrackState *request, int groupId);

void SpawnTrailEffect(EffectOwner *owner, const VecFx32 *origin, const VecFx32 *direction)
{
    EffectResources *resources = data_ov001_020a04bc;
    TrackState request;

    if (owner->effectSlot < 0) {
        ResetAnimationTrackState(&request);
        request.id = 0;
        request.loop = 0;
        VEC_MultAdd(-0x800, direction, origin, &request.position);
        request.angle = FX_Atan2Idx(direction->x, direction->z);
        request.scale = 0x2000;
        owner->effectSlot = func_ov021_020a8cc0(&request, resources->trailGroup);
    }
}
