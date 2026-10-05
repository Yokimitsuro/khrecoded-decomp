#include "nitro/types.h"
#include "nnsys/snd.h"

extern void func_02013178(NNSSndSeqPlayer *seqPlayer, BOOL flag);

void NNS_SndPlayerPause_0202a294(NNSSndHandle *handle, BOOL flag)
{
    func_02013178(handle->player, flag);
}
