#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_GetBackLight(PMBackLightSwitch *top, PMBackLightSwitch *bottom)
{
    u16 status;
    u32 result = PM_SendUtilityCommand(
        PM_UTIL_GET_STATUS,
        PM_UTIL_PARAM_BACKLIGHT,
        &status);

    if (result == PM_SUCCESS) {
        if (top != 0) {
            *top = (status & 8) != 0
                       ? PM_BACKLIGHT_ON
                       : PM_BACKLIGHT_OFF;
        }
        if (bottom != 0) {
            *bottom = (status & 4) != 0
                          ? PM_BACKLIGHT_ON
                          : PM_BACKLIGHT_OFF;
        }
    }
    return result;
}