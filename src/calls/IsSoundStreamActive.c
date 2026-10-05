#include "nitro/types.h"

extern u8 *gSoundWork;
extern int NNS_SndArcStrmGetCurrentPlayingPos(void *handle);

BOOL IsSoundStreamActive(int handleIndex)
{
    int result = NNS_SndArcStrmGetCurrentPlayingPos(gSoundWork + 0xb44c0 + handleIndex * 4);
    return result != 0;
}
