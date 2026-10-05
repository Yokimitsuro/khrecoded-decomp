#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 animId;
    s16 loopCount;
} AnimSequenceClip;

typedef struct {
    s8 state;
    s8 clipIndex;
    s8 clipCount;
    s8 loopCounter;
    AnimSequenceClip clips[4];
    fx32 frame;
    u8 pad_18[0x04];
    VecFx32 position;
    VecFx32 target;
    VecFx32 startPosition;
} AnimSequence;

void AnimSequence_Reset(AnimSequence *seq, VecFx32 *position, VecFx32 *target)
{
    seq->state = 1;
    seq->position = *position;
    seq->target = *target;
    seq->startPosition = *position;
    seq->clipIndex = 0;
    seq->loopCounter = 0;
    seq->frame = 0;
}
