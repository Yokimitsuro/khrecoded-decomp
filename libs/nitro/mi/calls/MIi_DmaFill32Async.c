#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DmaFill32Async(
    u32 dmaNo, void *destination, u32 data, u32 size,
    MIDmaCallback callback, void *arg, BOOL dmaEnable)
{
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
                    dmaNo, data, (u32)destination, MI_CNT_CLEAR32_IF(size),
                    MIi_DMA_MODE_SRC32);
            } else {
                MIi_DmaSetParameters(
                    dmaNo, data, (u32)destination, MI_CNT_SET_CLEAR32_IF(size),
                    MIi_DMA_MODE_SRC32 | MIi_DMA_MODE_NOCLEAR);
            }
        } else {
            if (dmaEnable) {
                MIi_DmaSetParameters(
                    dmaNo, data, (u32)destination, MI_CNT_CLEAR32(size),
                    MIi_DMA_MODE_SRC32);
            } else {
                MIi_DmaSetParameters(
                    dmaNo, data, (u32)destination, MI_CNT_SET_CLEAR32(size),
                    MIi_DMA_MODE_SRC32 | MIi_DMA_MODE_NOCLEAR);
            }
        }
    }
}
