#include "libs/nitro/spi/pm_power_internal.h"

u32 PMi_TryToSendPxiData(
    u32 *sendData,
    int count,
    u16 *returnValue,
    PMCallback callback,
    void *argument)
{
    int index;
    OSIntrMode interruptMode = OS_DisableInterrupts();

    if (PMi_Bss.work.lock) {
        (void)OS_RestoreInterrupts(interruptMode);
        return PM_BUSY;
    }

    PMi_Bss.work.lock = 1;
    PMi_Bss.work.work = returnValue;
    PMi_Bss.work.callback = callback;
    PMi_Bss.work.callbackArgument = argument;

    for (index = 0; index < count; index++) {
        PMi_SendPxiData(sendData[index]);
    }

    (void)OS_RestoreInterrupts(interruptMode);
    return PM_SUCCESS;
}