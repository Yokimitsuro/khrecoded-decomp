#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

void ZeroHalfThenFree(NNSSndSeqPlayer * seqPlayer, BOOL flag);
extern void ZeroHalfThenFree (NNSSndSeqPlayer * seqPlayer, BOOL flag);

void NNS_SndPlayerPause_0207b80c (NNSSndHandle * handle, BOOL flag)
{
    ZeroHalfThenFree(handle->player, flag);
}
