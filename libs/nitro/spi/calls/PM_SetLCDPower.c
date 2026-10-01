#include "libs/nitro/spi/pm_power_internal.h"

extern BOOL GX_IsDispOn(void);
extern void GX_DispOff(void);

BOOL PM_SetLCDPower(PMLCDPower power)
{
    if (power != PM_LCD_POWER_ON) {
        power = PM_LCD_POWER_OFF;
        if (GX_IsDispOn()) {
            GX_DispOff();
        }
    }

    return PMi_SetLCDPower(power, PM_LED_NONE, FALSE, TRUE);
}