#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DMACallback(void *unused)
{
    MIDmaCallback callback;
    void *arg;

    OS_DisableIrqMask(OS_IE_GXFIFO);

    REG_G3X_GXSTAT =
        ((u32)MIi_GXDmaParams.fifoCond << REG_G3X_GXSTAT_FI_SHIFT) |
        (REG_G3X_GXSTAT & ~REG_G3X_GXSTAT_FI_MASK);

    OS_SetIrqFunction(OS_IE_GXFIFO, MIi_GXDmaParams.fifoFunc);

    MIi_GXDmaParams.isBusy = 0;
    callback = MIi_GXDmaParams.callback;
    arg = MIi_GXDmaParams.arg;
    if (callback != 0) {
        callback(arg);
    }
}