#include "nitro/types.h"
#include "nnsys/snd.h"

extern u8 *data_0206084c;
extern int NNS_SndPlayerGetSeqNo(NNSSndHandle *handle);
extern int NNS_SndPlayerCountPlayingSeqBySeqNo(int seqNo);

BOOL IsCachedSeqPlaying(void)
{
    int seqNo = NNS_SndPlayerGetSeqNo((NNSSndHandle *)(data_0206084c + 0xb44d8));

    if (seqNo < 0) {
        goto notPlaying;
    }
    if (NNS_SndPlayerCountPlayingSeqBySeqNo(seqNo) != 0) {
        goto isPlaying;
    }
notPlaying:
    return FALSE;
isPlaying:
    return TRUE;
}
