#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00000[0xa4];
    int defaultSeqArcNo;
    u8 pad_000a8[0xb44dc - 0xa8];
    NNSSndHandle seHandle;
} SoundWork;

extern SoundWork *gSoundWork;
extern BOOL NNS_SndArcPlayerStartSeqArc(NNSSndHandle *handle, int seqArcNo, int index);

BOOL PlaySoundEffect(int seqArcNo, int index)
{
    if (seqArcNo == 0) {
        seqArcNo = gSoundWork->defaultSeqArcNo;
    }
    return NNS_SndArcPlayerStartSeqArc(&gSoundWork->seHandle, seqArcNo, index);
}
