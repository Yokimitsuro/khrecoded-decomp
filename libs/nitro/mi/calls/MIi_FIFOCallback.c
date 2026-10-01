#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_FIFOCallback(void)
{
    u32 length;
    u32 src;

    if (MIi_GXDmaParams.length == 0) {
        return;
    }

    length = MIi_GXDmaParams.length >= MIi_GX_LENGTH_ONCE
                 ? MIi_GX_LENGTH_ONCE
                 : MIi_GXDmaParams.length;
    src = MIi_GXDmaParams.src;

    MIi_GXDmaParams.length -= length;
    MIi_GXDmaParams.src += length;

    if (MIi_GXDmaParams.length == 0) {
        OSi_EnterDmaCallback(MIi_GXDmaParams.dmaNo, MIi_DMACallback, 0);
        MIi_DmaSetParameters(MIi_GXDmaParams.dmaNo, src, REG_GXFIFO_ADDR,
                             MI_CNT_SEND32_IF(length), 0);
        (void)OS_ResetRequestIrqMask(OS_IE_GXFIFO);
    } else {
        MIi_DmaSetParameters(MIi_GXDmaParams.dmaNo, src, REG_GXFIFO_ADDR,
                             MI_CNT_SEND32(length), 0);
        (void)OS_ResetRequestIrqMask(OS_IE_GXFIFO);
    }
}