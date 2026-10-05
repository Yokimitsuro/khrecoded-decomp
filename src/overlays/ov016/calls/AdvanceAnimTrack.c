#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 animId;
    u16 nodeIndex;
    fx32 speed;
    fx32 frame;
    fx32 maxFrame;
} AnimTrack;

BOOL AdvanceAnimTrack(void *obj, AnimTrack *track)
{
    BOOL finished = FALSE;

    track->frame += 0x1000;
    if (track->frame >= track->maxFrame) {
        track->frame = track->maxFrame;
        finished = TRUE;
    }
    return finished;
}
