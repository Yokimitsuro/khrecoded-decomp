#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 team;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x1C];
} HitParams;

typedef struct {
    s32 team;
    u8 pad_04[0x18C];
    s16 hitEffectId;
} HitOwner;

typedef struct {
    u8 pad_00[0x5A];
    u8 mode;
} EventSourceData;

typedef struct {
    u8 pad_00[4];
    EventSourceData *data;
} EventSource;

typedef struct {
    u8 pad_00[8];
    s32 type;
    VecFx32 position;
    EventSource *source;
} HitEvent;

extern void ResetAnimationTrackState(HitParams *params);
extern s32 func_ov021_020a8cc0(HitParams *params, s32 effectId);

void SpawnHitEffectOnEvent(HitOwner *owner, void *unused, HitEvent *event)
{
    BOOL shouldHit = FALSE;
    HitParams params;

    switch (event->type) {
    case 3:
        if (event->source->data->mode == 1) {
            shouldHit = TRUE;
        }
        break;
    case 2:
    case 4:
        shouldHit = TRUE;
        break;
    }
    if (shouldHit) {
        ResetAnimationTrackState(&params);
        params.team = owner->team;
        params.position = event->position;
        func_ov021_020a8cc0(&params, owner->hitEffectId);
    }
}
