#include "libs/nitro/spi/pm_power_internal.h"

u32 PMi_SendSleepStart(u16 trigger, u16 keyInterruptData)
{
    u32 sendData[2];

    sendData[0] = PMi_PXI_SYNC_PACKET;
    PMi_TryToSendPxiDataTillSuccess(sendData, 1);

    while (PMi_SetLCDPower(
               PM_LCD_POWER_OFF,
               PM_LED_BLINK_LOW,
               FALSE,
               1) != 1) {
    }

    sendData[0] = PMi_PXI_SLEEP_HEADER | (u8)trigger;
    sendData[1] = PMi_PXI_PARAMETER_HEADER |
                  (keyInterruptData & 0xffff);
    PMi_TryToSendPxiDataTillSuccess(sendData, 2);
    return PM_SUCCESS;
}
