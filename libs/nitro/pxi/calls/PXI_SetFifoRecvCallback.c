#include "libs/nitro/pxi/pxi_fifo_internal.h"

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

void PXI_SetFifoRecvCallback(int fifoTag, PXIFifoCallback callback)
{
    int enabled = OS_DisableInterrupts();
    int *systemWork = (int *)0x02fffc00;

    FifoRecvCallbackTable[fifoTag] = callback;
    if (callback != 0) {
        systemWork[0xe2] |= 1 << fifoTag;
    } else {
        systemWork[0xe2] &= ~(1 << fifoTag);
    }
    OS_RestoreInterrupts(enabled);
}
