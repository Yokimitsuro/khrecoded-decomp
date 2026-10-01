#include "libs/nitro/spi/pm_power_internal.h"

u32 PMi_SetLEDAsync(PMLEDStatus status, PMCallback callback, void *argument)
{
    u32 command;

    switch (status) {
    case PM_LED_ON:
        command = PM_UTIL_LED_ON;
        break;
    case PM_LED_BLINK_HIGH:
        command = PM_UTIL_LED_BLINK_HIGH_SPEED;
        break;
    case PM_LED_BLINK_LOW:
        command = PM_UTIL_LED_BLINK_LOW_SPEED;
        break;
    default:
        command = 0;
    }

    return command != 0
               ? PM_SendUtilityCommandAsync(command, 0, 0, callback, argument)
               : PM_INVALID_COMMAND;
}