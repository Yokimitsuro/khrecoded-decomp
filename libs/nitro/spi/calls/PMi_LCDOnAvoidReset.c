#include "libs/nitro/spi/pm_power_internal.h"

void PMi_LCDOnAvoidReset(void)
{
    int previousMethod;

    OS_SpinWait(PMi_LCD_WAIT_SYS_CYCLES);
    previousMethod = PMi_WaitBusyMethod;
    PMi_WaitBusyMethod = PMi_WAITBUSY_METHOD_CPUMODE |
                         PMi_WAITBUSY_METHOD_CPSR |
                         PMi_WAITBUSY_METHOD_IME;

    if (PM_GetLCDPower() != PM_LCD_POWER_ON) {
        while (PM_SetBackLight(PM_LCD_ALL, PM_BACKLIGHT_OFF) != PM_SUCCESS) {
            OS_SpinWait(PMi_ARM9_CLOCK_DIV_100);
        }
        while (!PM_SetLCDPower(PM_LCD_POWER_ON)) {
            OS_SpinWait(PMi_PXI_WAIT_TICK);
        }
    }
    PMi_WaitBusyMethod = previousMethod;
}