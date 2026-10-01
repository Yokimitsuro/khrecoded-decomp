#include "libs/nitro/spi/pm_power_internal.h"

u32 PMi_SetAmp(PMAmpSwitch status)
{
    if (PM_GetLCDPower() != PM_LCD_POWER_OFF) {
        return PM_SendUtilityCommand(
            PM_UTIL_SET_AMP,
            (u16)status,
            0);
    }
    return PM_SUCCESS;
}