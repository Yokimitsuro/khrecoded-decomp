#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_SendUtilityCommandAsync(
    u32 number,
    u16 parameter,
    u16 *returnValue,
    PMCallback callback,
    void *argument)
{
    u32 sendData[2];

    sendData[0] = PMi_PXI_UTILITY_HEADER | (u8)number;
    sendData[1] = PMi_PXI_PARAMETER_HEADER | (parameter & 0xffff);
    return PMi_TryToSendPxiData(
        sendData,
        2,
        returnValue,
        callback,
        argument);
}