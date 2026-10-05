#include "nitro/types.h"

extern u8 *gSoundWork;
extern void NNS_SndHeapLoadState(void *heap, s32 level);

void ReleaseSeqArcHeapLevel(int index)
{
    s32 level = *(s32 *)(gSoundWork + index * 4 + 0xa8);

    if (level < 0) {
        return;
    }
    NNS_SndHeapLoadState(*(void **)(gSoundWork + 0xb04b4), level);
}
