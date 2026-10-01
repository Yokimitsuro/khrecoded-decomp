#include "libs/nitro/spi/pm_power_internal.h"

void PM_Init(void)
{
    if (PMi_Bss.isInitialized) {
        return;
    }

    PMi_Bss.isInitialized = 1;
    PMi_Bss.work.lock = FALSE;
    PMi_Bss.work.callback = 0;

    PXI_Init();
    while (!PXI_IsCallbackReady(PXI_FIFO_TAG_PM, PXI_PROC_ARM7)) {
        WaitByLoop(100);
    }
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_PM, PMi_CommonCallback);

    PMi_Bss.lcdCount = PMi_Bss.displayOffCount = OS_VBLANK_COUNT;
}
