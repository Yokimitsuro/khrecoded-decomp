#include "nitro/types.h"

typedef struct NNSSndHandle NNSSndHandle;

extern u8 *data_0206084c;
extern void NNS_SndPlayerStopSeq(NNSSndHandle *handle, BOOL flag);

void PauseBgmForState(BOOL pause)
{
    u8 *scene = data_0206084c;

    *(s16 *)(scene + 0xb472a) = -1;
    NNS_SndPlayerStopSeq((NNSSndHandle *)(scene + 0xb44d8), pause);
    *(BOOL *)(scene + 0xb4730) = pause;
    scene[0xb472e] = 4;
}
