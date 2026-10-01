#include "libs/nitro/spi/pm_power_internal.h"

u32 PMi_ForceToPowerOff(void)
{
    while (PM_ForceToPowerOff() != PM_SUCCESS) {
        OS_SpinWait(PMi_ARM9_CLOCK_DIV_100);
    }

    (void)OS_DisableInterrupts();
    MI_StopAllDma();
    while (1) {
        OS_Halt();
    }
}