#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_ForceToPowerOff(void)
{
    u32 commandResult;
    u32 sendResult = PM_ForceToPowerOffAsync(
        PMi_DummyCallback,
        &commandResult);

    if (sendResult == PM_SUCCESS) {
        PMi_WaitBusyMethod = PMi_WAITBUSY_METHOD_CPSR |
                             PMi_WAITBUSY_METHOD_IME;
        PMi_WaitBusy();
        PMi_WaitBusyMethod = PMi_WAITBUSY_METHOD_CPUMODE;
        return commandResult;
    }
    return sendResult;
}