#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType)
{
    int channel;
    u32 control;
    u32 timing;

    for (channel = 0; channel < MI_DMA_MAX_NUM; channel++) {
        if (channel == dmaNo) {
            continue;
        }

        control = *(vu32 *)(MI_DMA_REGISTER_BASE + MI_DMA_CONTROL_OFFSET +
                            channel * MI_DMA_CHANNEL_STRIDE);
        if ((control & MI_DMA_ENABLE) == 0) {
            continue;
        }

        timing = control & MI_DMA_TIMING_ONLY_MASK;
        if (timing == dmaType ||
            (timing == MI_DMA_TIMING_V_BLANK && dmaType == MI_DMA_TIMING_H_BLANK) ||
            (timing == MI_DMA_TIMING_H_BLANK && dmaType == MI_DMA_TIMING_V_BLANK)) {
            continue;
        }

        if (timing == MI_DMA_TIMING_DISP ||
            timing == MI_DMA_TIMING_DISP_MMEM ||
            timing == MI_DMA_TIMING_CARD ||
            timing == MI_DMA_TIMING_CARTRIDGE ||
            timing == MI_DMA_TIMING_GXFIFO ||
            timing == MI_DMA_TIMING_V_BLANK ||
            timing == MI_DMA_TIMING_H_BLANK) {
            OS_Terminate();
        }
    }
}