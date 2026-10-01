#include "libs/nitro/mi/mi_dma_internal.h"

void MI_StopDma(u32 dmaNo)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    u32 offset = dmaNo * MI_DMA_CHANNEL_STRIDE;
    vu32 *control = (vu32 *)(MI_DMA_REGISTER_BASE + MI_DMA_CONTROL_OFFSET + offset);

    *control &= ~MI_DMA_TIMING_MASK;
    *control &= ~MI_DMA_ENABLE;
    *control;
    *control;

    if (dmaNo == 0) {
        vu32 *registers = (vu32 *)(MI_DMA_REGISTER_BASE + offset);
        registers[0] = 0;
        registers[1] = 0;
        registers[2] = MI_DMA0_CLEAR_DATA;
    }

    OS_RestoreInterrupts(enabled);
}