#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DmaFill32(
    u32 dmaNo, void *destination, u32 data, u32 size, BOOL dmaEnable)
{
    vu32 *dmaControl;

    if (size > 0) {
        dmaControl = MI_DMA_CONTROL(dmaNo);
        while (*dmaControl & MI_DMA_ENABLE) {
        }

        if (dmaEnable) {
            MIi_DmaSetParameters(
                dmaNo, data, (u32)destination, MI_CNT_CLEAR32(size),
                MIi_DMA_MODE_WAIT | MIi_DMA_MODE_SRC32);
        } else {
            MIi_DmaSetParameters(
                dmaNo, data, (u32)destination, MI_CNT_SET_CLEAR32(size),
                MIi_DMA_MODE_WAIT | MIi_DMA_MODE_SRC32 |
                    MIi_DMA_MODE_NOCLEAR);
        }

        while (*dmaControl & MI_DMA_ENABLE) {
        }
    }
}
