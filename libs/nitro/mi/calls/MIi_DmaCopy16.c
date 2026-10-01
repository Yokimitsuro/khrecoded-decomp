#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DmaCopy16(
    u32 dmaNo, const void *source, void *destination, u32 size, BOOL dmaEnable)
{
    vu32 *dmaControl;

    if (size > 0) {
        MIi_CheckDma0SourceAddress(dmaNo, (u32)source, size, 0);

        dmaControl = MI_DMA_CONTROL(dmaNo);
        while (*dmaControl & MI_DMA_ENABLE) {
        }

        if (dmaEnable) {
            MIi_DmaSetParameters(
                dmaNo, (u32)source, (u32)destination, MI_CNT_COPY16(size),
                MIi_DMA_MODE_WAIT);
        } else {
            MIi_DmaSetParameters(
                dmaNo, (u32)source, (u32)destination, MI_CNT_SET_COPY16(size),
                MIi_DMA_MODE_WAIT | MIi_DMA_MODE_NOCLEAR);
        }

        while (*dmaControl & MI_DMA_ENABLE) {
        }
    }
}
