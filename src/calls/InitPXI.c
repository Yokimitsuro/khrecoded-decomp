#include "nitro/types.h"

#define PXI_FIFO_TAG_SOUND 7
#define PXI_PROC_ARM7 1

extern void PXI_SetFifoRecvCallback(u32 fifoTag, void *callback);
extern BOOL PXI_IsCallbackReady(u32 fifoTag, int proc);
extern int IsCommandAvailable(void);
extern void PxiFifoCallback(int tag, int data);
extern void OS_SpinWait(u32 cycles);

void InitPXI(void)
{
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_SOUND, PxiFifoCallback);

    if (IsCommandAvailable()) {
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_SOUND, PXI_PROC_ARM7)) {
            OS_SpinWait(50);
        }
    }
}
