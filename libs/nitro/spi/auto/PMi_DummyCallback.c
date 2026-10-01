#include "libs/nitro/spi/pm_power_internal.h"

void PMi_DummyCallback(u32 result, void *argument)
{
    if (argument != 0) {
        *(u32 *)argument = result;
    }
}