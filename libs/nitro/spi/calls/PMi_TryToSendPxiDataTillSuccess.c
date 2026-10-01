#include "libs/nitro/spi/pm_power_internal.h"

void PMi_TryToSendPxiDataTillSuccess(u32 *sendData, int count)
{
    volatile u32 result;

    while (1) {
        result = PMi_UNUSED_RESULT;
        while (PMi_TryToSendPxiData(
                   sendData,
                   count,
                   0,
                   PMi_DummyCallback,
                   (void *)&result) != PM_SUCCESS) {
            OS_SpinWait(PMi_ARM9_CLOCK_DIV_100);
        }

        while (result == PMi_UNUSED_RESULT) {
            OS_SpinWait(PMi_ARM9_CLOCK_DIV_100);
        }
        if (result == PM_SUCCESS) {
            break;
        }

        OS_SpinWait(PMi_ARM9_CLOCK_DIV_100);
    }
}