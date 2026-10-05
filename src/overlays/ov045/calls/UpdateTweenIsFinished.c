#include "nitro/types.h"

typedef struct {
    u8 pad00[0x18];
    u32 unused0 : 2;
    u32 finished : 1;
} Tween;

extern void SampleTweenValue(Tween *tween_state, s32 *output_value);

BOOL UpdateTweenIsFinished(Tween *tween)
{
    SampleTweenValue(tween, NULL);
    return tween->finished;
}
