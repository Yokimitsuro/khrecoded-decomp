#include "nitro/types.h"

typedef void (*TPRecvCallback)(int result, int operation, int detail);

struct TPSample {
    u32 xy00;
    u16 touch04;
    u16 validity06;
};

struct TPState {
    u8 pad00[4];
    TPRecvCallback callback04;
    u8 pad08[8];
    u16 index10;
    u16 frequence12;
    struct TPSample *samplingBufs14;
    u16 bufSize18;
    u8 pad1a[0x1e];
    u16 errFlags38;
    u16 commandFlags3a;
};

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int PXI_SendWordByFifo(int channel, int word, int flag);
extern struct TPState data_02059784;

void TP_RequestAutoSamplingStartAsync(int vcount, int frequence,
                   char *samplingBufs, unsigned int bufSize)
{
    void (*callback)(int, int, int);
    int i;
    int interruptState;
    int ok;
    int result;

    data_02059784.samplingBufs14 = (struct TPSample *)samplingBufs;
    data_02059784.index10 = 0;
    data_02059784.frequence12 = (short)frequence;
    data_02059784.bufSize18 = (short)bufSize;

    for (i = 0; i < bufSize; i++) {
        data_02059784.samplingBufs14[i].touch04 = 0;
    }

    interruptState = OS_DisableInterrupts();
    if (PXI_SendWordByFifo(6, (frequence & 0xff) | 0x100 | 0x2000000, 0) < 0) {
        ok = 0;
    } else {
        result = PXI_SendWordByFifo(6, vcount | 0x10000 | 0x1000000, 0);
        if (result < 0) {
            ok = 0;
        } else {
            ok = 1;
        }
    }

    if ((ok & 0xff) == 0) {
        OS_RestoreInterrupts(interruptState);
        data_02059784.errFlags38 |= 2;
        callback = data_02059784.callback04;
        if (callback == 0) {
            return;
        }
        callback(1, 4, 0);
        return;
    }

    {
        data_02059784.commandFlags3a |= 2;
        data_02059784.errFlags38 &= ~2;
    }
    OS_RestoreInterrupts(interruptState);
}
