#include "libs/nitro/spi/pm_power_internal.h"

void PMi_WaitVBlank(void)
{
    volatile u32 count = OS_VBLANK_COUNT;

    while (1) {
        u32 current = OS_VBLANK_COUNT;
        if (count != current) {
            return;
        }
    }
}