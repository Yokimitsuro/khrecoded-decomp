#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_SetBackLightAsync(
    PMLCDTarget target,
    PMBackLightSwitch state,
    PMCallback callback,
    void *argument)
{
    u32 command = 0;

    if (target == PM_LCD_TOP) {
        if (state == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD2_BACKLIGHT_ON;
        }
        if (state == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD2_BACKLIGHT_OFF;
        }
    } else if (target == PM_LCD_BOTTOM) {
        if (state == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD1_BACKLIGHT_ON;
        }
        if (state == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD1_BACKLIGHT_OFF;
        }
    } else if (target == PM_LCD_ALL) {
        if (state == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD12_BACKLIGHT_ON;
        }
        if (state == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD12_BACKLIGHT_OFF;
        }
    }

    return command != 0
               ? PM_SendUtilityCommandAsync(command, 0, 0, callback, argument)
               : PM_INVALID_COMMAND;
}