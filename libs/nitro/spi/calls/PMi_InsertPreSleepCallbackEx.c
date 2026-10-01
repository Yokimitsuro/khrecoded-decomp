#include "libs/nitro/spi/calls/pm_callback_internal.h"

void PMi_InsertPreSleepCallbackEx(PMGenCallbackInfo *info, int priority)
{
    PMi_InsertList(&PMi_PreSleepCallbackList, info, priority, PMi_COMPARE_GT);
}
