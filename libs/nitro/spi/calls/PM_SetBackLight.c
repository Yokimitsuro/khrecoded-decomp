#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_SetBackLight(PMLCDTarget target, PMBackLightSwitch state)
{
    u32 commandResult;
    u32 sendResult = PM_SetBackLightAsync(
        target, state, PMi_DummyCallback, &commandResult);

    if (sendResult == PM_SUCCESS) {
        PMi_WaitBusy();
        return commandResult;
    }
    return sendResult;
}