#include "libs/nitro/mi/mi_dma_internal.h"

void MIi_DMAFastCallback(void *unused)
{
    MIDmaCallback callback;
    void *arg;

    (void)unused;
    MIi_GXDmaParams.isBusy = 0;
    callback = MIi_GXDmaParams.callback;
    arg = MIi_GXDmaParams.arg;
    if (callback != 0) {
        callback(arg);
    }
}
