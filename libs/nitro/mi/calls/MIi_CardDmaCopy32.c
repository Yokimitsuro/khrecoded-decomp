#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size)
{
    vu32 *dmaControl;

    MIi_CheckAnotherAutoDMA(dmaNo, MI_DMA_TIMING_ANY);
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_FIX);

    if (size == 0) {
        return;
    }

    dmaControl = MI_DMA_CONTROL(dmaNo);
    while (*dmaControl & MI_DMA_ENABLE) {
    }

    MIi_DmaSetParameters(dmaNo, (u32)src, (u32)dest,
                         MI_CNT_CARDRECV32_CONTINUOUS, 0);
}