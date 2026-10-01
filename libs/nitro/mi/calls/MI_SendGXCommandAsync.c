#include "libs/nitro/mi/mi_dma_internal.h"

void MI_SendGXCommandAsync(
    u32 dmaNo, const void *src, u32 commandLength,
    MIDmaCallback callback, void *arg)
{
    if (commandLength == 0) {
        if (callback != 0) {
            callback(arg);
        }
        return;
    }

    while (MIi_GXDmaParams.isBusy) {
    }
    while (!(((REG_G3X_GXSTAT & REG_G3X_GXSTAT_FIFOSTAT_MASK) >>
              REG_G3X_GXSTAT_FIFOSTAT_SHIFT) & GX_FIFOSTAT_UNDERHALF)) {
    }

    MIi_GXDmaParams.isBusy = 1;
    MIi_GXDmaParams.dmaNo = dmaNo;
    MIi_GXDmaParams.src = (u32)src;
    MIi_GXDmaParams.length = commandLength;
    MIi_GXDmaParams.callback = callback;
    MIi_GXDmaParams.arg = arg;

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, commandLength, MI_DMA_SRC_INC);
    MI_WaitDma(dmaNo);

    {
        OSIntrMode enabled = OS_DisableInterrupts();

        MIi_GXDmaParams.fifoCond =
            (GXFifoIntrCond)((REG_G3X_GXSTAT & REG_G3X_GXSTAT_FI_MASK) >>
                             REG_G3X_GXSTAT_FI_SHIFT);
        MIi_GXDmaParams.fifoFunc = OS_GetIrqFunction(OS_IE_GXFIFO);

        REG_G3X_GXSTAT =
            (REG_G3X_GXSTAT & ~REG_G3X_GXSTAT_FI_MASK) |
            (GX_FIFOINTR_COND_UNDERHALF << REG_G3X_GXSTAT_FI_SHIFT);
        OS_SetIrqFunction(OS_IE_GXFIFO, MIi_FIFOCallback);
        (void)OS_EnableIrqMask(OS_IE_GXFIFO);
        MIi_FIFOCallback();
        (void)OS_RestoreInterrupts(enabled);
    }
}