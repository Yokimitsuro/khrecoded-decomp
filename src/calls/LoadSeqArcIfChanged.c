#include "nitro/types.h"
#include "nnsys/snd.h"

extern u8 *gSoundWork;
extern int NNS_SndHeapSaveState(NNSSndHeapHandle heap);
extern void NNS_SndHeapLoadState(NNSSndHeapHandle heap, int level);
extern void FSi_WaitForCardThread(void);
extern void SoundMgr_WaitLoaderIfState1(void);
extern BOOL NNS_SndArcLoadSeqArc(int seqNo, NNSSndHeapHandle heap);

void LoadSeqArcIfChanged(int seqArcNo)
{
    u8 *base = gSoundWork;
    int index;

    if (*(int *)(base + 0xa4) == seqArcNo) {
        NNS_SndHeapLoadState(*(NNSSndHeapHandle *)(base + 0xb04b4), *(int *)(base + 0xa0));
    } else {
        *(int *)(base + 0xa4) = seqArcNo;
        FSi_WaitForCardThread();
        SoundMgr_WaitLoaderIfState1();
        NNS_SndHeapLoadState(*(NNSSndHeapHandle *)(base + 0xb04b4), *(int *)(base + 0xa8));
        NNS_SndArcLoadSeqArc(seqArcNo, *(NNSSndHeapHandle *)(base + 0xb04b4));
        *(int *)(base + 0xa0) = NNS_SndHeapSaveState(*(NNSSndHeapHandle *)(base + 0xb04b4));
    }

    for (index = 0; index < 3; index++) {
        *(int *)(base + index * 4 + 0xa8) = 0;
    }

    *(s16 *)(base + 0xb4736) = -1;
    *(u16 *)(base + 0xb4734) = 0;
}
