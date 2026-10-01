#include "libs/nitro/spi/pm_power_internal.h"

void PMi_CallCallbackAndUnlock(u32 result)
{
    PMCallback callback = PMi_Bss.work.callback;
    void *argument = PMi_Bss.work.callbackArgument;

    PMi_Bss.work.lock = FALSE;
    if (callback != 0) {
        PMi_Bss.work.callback = 0;
        callback(result, argument);
    }
}