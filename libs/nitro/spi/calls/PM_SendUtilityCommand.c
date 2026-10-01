#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_SendUtilityCommand(u32 number, u16 parameter, u16 *returnValue)
{
    u32 commandResult;
    u32 sendResult = PM_SendUtilityCommandAsync(
        number,
        parameter,
        returnValue,
        PMi_DummyCallback,
        &commandResult);

    if (sendResult == PM_SUCCESS) {
        PMi_WaitBusy();
        return commandResult;
    }
    return sendResult;
}