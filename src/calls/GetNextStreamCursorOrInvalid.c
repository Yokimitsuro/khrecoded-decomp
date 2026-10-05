#include "nitro/types.h"

extern u8 *gSoundWork;
extern int NNS_SndArcStrmGetCurrentPlayingPos(void *handle);
extern u32 NNS_SndArcStrmGetTimeLength(void *handle);

u32 GetNextStreamCursorOrInvalid(int handleIndex)
{
    u32 next = NNS_SndArcStrmGetCurrentPlayingPos(gSoundWork + 0xb44c0 + handleIndex * 4) + 1;
    u32 limit = NNS_SndArcStrmGetTimeLength(gSoundWork + 0xb44c0 + handleIndex * 4);

    if (next >= limit) {
        next = 0xffffffff;
    }
    return next;
}
