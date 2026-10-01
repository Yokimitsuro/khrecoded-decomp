#include "libs/nitro/os/os_tick_internal.h"

BOOL OS_IsTickAvailable(void)
{
    return OSi_TickState.useTick;
}