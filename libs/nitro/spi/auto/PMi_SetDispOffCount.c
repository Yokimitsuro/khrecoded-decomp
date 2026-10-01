#include "libs/nitro/spi/pm_power_internal.h"

void PMi_SetDispOffCount(void)
{
    PMi_Bss.displayOffCount = OS_VBLANK_COUNT;
}
