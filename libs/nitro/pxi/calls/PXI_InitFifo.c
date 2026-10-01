#include "libs/nitro/pxi/pxi_fifo_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
extern u32 OS_ResetRequestIrqMask(u32 mask);
extern void OS_SetIrqFunction(u32 mask, void (*function)(void));
extern u32 OS_EnableIrqMask(u32 mask);

#define PXI_FIFO_COUNT (*(volatile u16 *)0x04000184)
#define PXI_INTF (*(volatile u16 *)0x04000180)
#define PXI_FIFO_COUNT_INIT 0xc408
#define OS_IE_FIFO_RECV (1U << 18)
#define PXI_PROC_ARM 0
#define PXI_MAX_FIFO_TAG 32
#define TRUE 1
#define NULL 0

void PXI_InitFifo(void)
{
    int i;
    OSIntrMode enabled;
    OSSystemWork *systemWork = (OSSystemWork *)0x02fffc00;

    enabled = OS_DisableInterrupts();

    if (!FifoCtrlInit) {
        FifoCtrlInit = TRUE;
        systemWork->pxiHandleChecker[PXI_PROC_ARM] = 0;

        for (i = 0; i < PXI_MAX_FIFO_TAG; i++) {
            FifoRecvCallbackTable[i] = NULL;
        }

        PXI_FIFO_COUNT = PXI_FIFO_COUNT_INIT;
        (void)OS_ResetRequestIrqMask(OS_IE_FIFO_RECV);
        OS_SetIrqFunction(OS_IE_FIFO_RECV, PXIi_HandlerRecvFifoNotEmpty);
        (void)OS_EnableIrqMask(OS_IE_FIFO_RECV);

        {
            int timeout;
            s32 value;

            for (i = 0;; i++) {
                value = PXI_INTF & 15;
                PXI_INTF = (u16)(value << 8);

                if (value == 0 && i > 4) {
                    break;
                }

                for (timeout = 1000; (PXI_INTF & 15) == value; timeout--) {
                    if (timeout == 0) {
                        i = 0;
                        break;
                    }
                }
            }
        }
    }

    (void)OS_RestoreInterrupts(enabled);
}
