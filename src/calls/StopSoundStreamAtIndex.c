#include "nitro/types.h"

extern u8 *data_0206084c;
extern void NNS_SndArcStrmStop(void *handle, int fadeFrame);

void StopSoundStreamAtIndex(int handleIndex, int fadeFrame)
{
    NNS_SndArcStrmStop(data_0206084c + 0xb44c0 + handleIndex * 4, fadeFrame);
}
