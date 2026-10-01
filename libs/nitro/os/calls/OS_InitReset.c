#include "libs/nitro/os/os_reset_internal.h"

extern volatile u16 OSi_IsInitReset;
extern void PXI_Init(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*callback)(int, unsigned int));
extern void OSi_CommonCallback(int, unsigned int);

void OS_InitReset(void)
{
    if (OSi_IsInitReset != 0) {
        return;
    }
    OSi_IsInitReset = 1;

    PXI_Init();
    while (!PXI_IsCallbackReady(12, 1)) {
    }
    PXI_SetFifoRecvCallback(12, OSi_CommonCallback);
}
