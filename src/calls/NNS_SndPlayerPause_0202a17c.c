#include "nitro/types.h"
#include "nnsys/snd.h"

extern void PXI_Init_0201313c(NNSSndSeqPlayer *seqPlayer, BOOL flag);

void NNS_SndPlayerPause_0202a17c(NNSSndHandle *handle, BOOL flag)
{
    PXI_Init_0201313c(handle->player, flag);
}
