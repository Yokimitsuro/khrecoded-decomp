#include "libs/nitro/mi/mi_dma_internal.h"

void MI_SendGXCommandAsyncFast(
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

    MIi_GXDmaParams.isBusy = 1;
    MIi_GXDmaParams.dmaNo = dmaNo;
    MIi_GXDmaParams.callback = callback;
    MIi_GXDmaParams.arg = arg;

    MIi_CheckAnotherAutoDMA(dmaNo, MI_DMA_TIMING_GXFIFO);
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, commandLength, MI_DMA_SRC_INC);
    MI_WaitDma(dmaNo);

    OSi_EnterDmaCallback(dmaNo, MIi_DMAFastCallback, 0);
    MIi_DmaSetParameters(dmaNo, (u32)src, REG_GXFIFO_ADDR,
                         MI_CNT_GXCOPY_IF(commandLength), 0);
}