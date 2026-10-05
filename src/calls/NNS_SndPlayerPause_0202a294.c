#include "nitro/types.h"
#include "nnsys/snd.h"

extern void FreeExpandedHeapBlock(NNSSndSeqPlayer *seqPlayer, BOOL flag);

void NNS_SndPlayerPause_0202a294(NNSSndHandle *handle, BOOL flag)
{
    FreeExpandedHeapBlock(handle->player, flag);
}
