#include "nitro/types.h"

extern u8 *data_0206084c;
extern int NNS_SndArcStrmGetCurrentPlayingPos(void *handle);

BOOL IsSoundStreamActive(int handleIndex)
{
    int result = NNS_SndArcStrmGetCurrentPlayingPos(data_0206084c + 0xb44c0 + handleIndex * 4);
    return result != 0;
}
