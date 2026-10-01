#include "libs/nitro/spi/pm_power_internal.h"

u32 PM_ForceToPowerOffAsync(PMCallback callback, void *argument)
{
    PMi_LCDOnAvoidReset();
    return PM_SendUtilityCommandAsync(
        PM_UTIL_FORCE_POWER_OFF,
        0,
        0,
        callback,
        argument);
}