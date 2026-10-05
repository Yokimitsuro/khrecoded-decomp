#include "nitro/types.h"
#include "nnsys/snd.h"

extern u8 *data_0206084c;
extern void NNS_SndHeapClear(NNSSndHeapHandle heap);
extern void QueueTypedMessage(u16 messageId, int arg1, int arg2);

void RequestSoundLoad(u32 soundId)
{
    u8 *base = data_0206084c;

    *(u8 *)(base + 0xb472e) = 1;
    *(u16 *)(base + 0xb472a) = (u16)soundId;
    NNS_SndHeapClear(*(NNSSndHeapHandle *)(base + 0xb04b8));
    QueueTypedMessage((u16)soundId, *(int *)(base + 0xb04b8), (int)(base + 0xb472e));
}
