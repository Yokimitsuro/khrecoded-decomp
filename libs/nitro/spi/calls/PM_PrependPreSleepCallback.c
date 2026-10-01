#include "libs/nitro/spi/calls/pm_callback_internal.h"

void PM_PrependPreSleepCallback(PMGenCallbackInfo *info)
{
    PMi_InsertList(
        &PMi_PreSleepCallbackList,
        info,
        PM_CALLBACK_PRIORITY_MIN,
        PMi_COMPARE_GE);
}
