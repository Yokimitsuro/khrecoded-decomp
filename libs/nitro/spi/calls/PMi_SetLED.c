#include "libs/nitro/spi/pm_power_internal.h"

u32 PMi_SetLED(PMLEDStatus status)
{
    u32 commandResult;
    u32 sendResult = PMi_SetLEDAsync(
        status,
        PMi_DummyCallback,
        &commandResult);

    if (sendResult == PM_SUCCESS) {
        PMi_WaitBusy();
        return commandResult;
    }
    return sendResult;
}