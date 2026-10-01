#include "libs/nitro/spi/calls/pm_callback_internal.h"

void PM_AppendPostSleepCallback(PMGenCallbackInfo *info)
{
    PMi_InsertList(
        &PMi_PostSleepCallbackList,
        info,
        PM_CALLBACK_PRIORITY_MAX,
        PMi_COMPARE_GT);
}
