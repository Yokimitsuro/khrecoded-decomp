#include "nitro/types.h"

extern u8 *gSoundWork;
extern u32 QueueTypedMessageWithHandle(u16 a, u16 b, u32 c, void *arg);
extern void func_0202c44c(void);
extern u32 NNS_SndArcGetSeqArcSeqCount(u32 seqArcNo);
extern void NNS_SndArcGetSeqArcIdxSymbol(u32 seqArcNo, u32 index);

void QueueSoundCommandForArc(u32 seqArcNo, u32 unused2, u32 unused3, u32 commandArg)
{
    u32 count;
    u32 i = 0;
    u8 flagBuf[4];
    u32 valueBuf;

    flagBuf[0] = 0;
    valueBuf = commandArg;
    QueueTypedMessageWithHandle((u16)(seqArcNo & 0xffff), (u16)((seqArcNo + 0x29) & 0xffff),
                  *(u32 *)(gSoundWork + 0xb04b4), flagBuf);
    func_0202c44c();
    count = NNS_SndArcGetSeqArcSeqCount(seqArcNo);
    if (count != 0) {
        do {
            NNS_SndArcGetSeqArcIdxSymbol(seqArcNo, i);
            i = i + 1;
        } while (i < count);
    }
}
