#include "nitro/types.h"

extern u8 *gSoundWork;
extern void NNS_SndPlayerStopSeq(void *handle, BOOL flag);
extern void FreeSoundHandleSlot(void *entry);

void StopSoundSeqHandle(u32 handle)
{
    u8 *entry = gSoundWork + 0xb4518 + (handle >> 24) * 0x20;

    if (*(u16 *)(entry + 0x14) == 0) {
        return;
    }
    if (*(u32 *)(entry + 0x18) != (handle & 0xffffff)) {
        return;
    }
    NNS_SndPlayerStopSeq(entry + 0x1c, 0);
    FreeSoundHandleSlot(entry);
}
