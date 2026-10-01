#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DmaCopy32Async(
    u32 dmaNo, const void *source, void *destination, u32 size,
    MIDmaCallback callback, void *arg, BOOL dmaEnable)
{
    MIi_CheckDma0SourceAddress(dmaNo, (u32)source, size, 0);

    if (size == 0) {
        if (callback) {
            callback(arg);
        }
    } else {
        MI_WaitDma(dmaNo);

        if (callback) {
            OSi_EnterDmaCallback(dmaNo, callback, arg);
            if (dmaEnable) {
                MIi_DmaSetParameters(
                    dmaNo, (u32)source, (u32)destination,
                    MI_CNT_COPY32_IF(size), 0);
            } else {
                MIi_DmaSetParameters(
                    dmaNo, (u32)source, (u32)destination,
                    MI_CNT_SET_COPY32_IF(size), MIi_DMA_MODE_NOCLEAR);
            }
        } else {
            if (dmaEnable) {
                MIi_DmaSetParameters(
                    dmaNo, (u32)source, (u32)destination,
                    MI_CNT_COPY32(size), 0);
            } else {
                MIi_DmaSetParameters(
                    dmaNo, (u32)source, (u32)destination,
                    MI_CNT_SET_COPY32(size), MIi_DMA_MODE_NOCLEAR);
            }
        }
    }
}
