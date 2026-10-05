#include "nitro/types.h"

extern u8 *data_0206084c;
extern void NNS_SndHeapLoadState(void *heap, s32 level);

void ReleaseSeqArcHeapLevel(int index)
{
    s32 level = *(s32 *)(data_0206084c + index * 4 + 0xa8);

    if (level < 0) {
        return;
    }
    NNS_SndHeapLoadState(*(void **)(data_0206084c + 0xb04b4), level);
}
