#include "nitro/types.h"

extern u8 *gSoundWork;
extern BOOL NNS_SndArcStrmPrepare(void *handle, int strmNo, u32 offset);

void OpenSoundStream(int handleIndex, int strmNo)
{
    NNS_SndArcStrmPrepare(gSoundWork + 0xb44c0 + handleIndex * 4, strmNo, 0);
}
