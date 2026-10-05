#include "nitro/types.h"

extern u8 *gSoundWork;
extern void NNS_SndArcStrmStop(void *handle, int fadeFrame);

void StopSoundStreamAtIndex(int handleIndex, int fadeFrame)
{
    NNS_SndArcStrmStop(gSoundWork + 0xb44c0 + handleIndex * 4, fadeFrame);
}
