#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackRequest {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x25 - 0x10];
    u8 looping;
    u8 pad_26[0x2c - 0x26];
} TrackRequest;

typedef struct HitEvent {
    u8 pad_00[8];
    int type;
    VecFx32 position;
} HitEvent;

typedef struct EffectSource {
    u8 pad_000[0x3c];
    s8 trackId;
    u8 pad_03d[0x18c - 0x3d];
    s16 groupId;
} EffectSource;

extern void ResetAnimationTrackState(TrackRequest *state);
extern int func_ov021_020a8cc0(TrackRequest *request, int groupId);

void PlayTrackOnHitEvent(EffectSource *source, u32 unused, HitEvent *event)
{
    TrackRequest request;
    if (event->type == 4) {
        ResetAnimationTrackState(&request);
        request.id = source->trackId;
        request.looping = 0;
        request.position = event->position;
        func_ov021_020a8cc0(&request, source->groupId);
    }
}
