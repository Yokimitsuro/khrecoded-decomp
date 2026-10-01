#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DmaSetParameters(
    u32 dmaNo, u32 source, u32 destination, u32 control, u32 mode)
{
    OSIntrMode enabled;
    vu32 *registers;

    if (!(mode & MIi_DMA_MODE_NOINT)) {
        enabled = OS_DisableInterrupts();
    }

    registers =
        (vu32 *)(MI_DMA_REGISTER_BASE + dmaNo * MI_DMA_CHANNEL_STRIDE);

    if (mode & MIi_DMA_MODE_SRC32) {
        MIiDmaClearSource *clearSource =
            (MIiDmaClearSource *)(MI_DMA_CLEAR_DATA_BASE + dmaNo * 4);
        clearSource->word = source;
        source = (u32)clearSource;
    } else if (mode & MIi_DMA_MODE_SRC16) {
        MIiDmaClearSource *clearSource =
            (MIiDmaClearSource *)(MI_DMA_CLEAR_DATA_BASE + dmaNo * 4);
        clearSource->halfword = (u16)source;
        source = (u32)clearSource;
    }

    registers[0] = source;
    registers[1] = destination;
    registers[2] = control;

    if (mode & MIi_DMA_MODE_WAIT) {
        u32 dummy;

        dummy = *(vu32 *)MI_DMA_REGISTER_BASE;
        dummy = *(vu32 *)MI_DMA_REGISTER_BASE;

        if (!(mode & MIi_DMA_MODE_NOCLEAR) && dmaNo == 0) {
            registers[0] = 0;
            registers[1] = 0;
            registers[2] = MI_DMA0_CLEAR_DATA;
        }
    }

    if (!(mode & MIi_DMA_MODE_NOINT)) {
        OS_RestoreInterrupts(enabled);
    }

    if (mode & MIi_DMA_MODE_WAIT) {
        u32 dummy;

        dummy = *(vu32 *)MI_DMA_REGISTER_BASE;
        dummy = *(vu32 *)MI_DMA_REGISTER_BASE;
    }
}
