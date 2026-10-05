#include "nitro/types.h"

extern u8 *data_0206084c;
extern int NNS_SndArcStrmGetCurrentPlayingPos(void *handle);
extern u32 NNS_SndArcStrmGetTimeLength(void *handle);

u32 GetNextStreamCursorOrInvalid(int handleIndex)
{
    u32 next = NNS_SndArcStrmGetCurrentPlayingPos(data_0206084c + 0xb44c0 + handleIndex * 4) + 1;
    u32 limit = NNS_SndArcStrmGetTimeLength(data_0206084c + 0xb44c0 + handleIndex * 4);

    if (next >= limit) {
        next = 0xffffffff;
    }
    return next;
}
