#include "libs/nitro/os/os_alarm_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern u32 OS_EnableIrqMask(u32 mask);

void OSi_SetTimer(OSAlarm *alarm)
{
    s64 delta;
    OSTick tick = OS_GetTick();
    u16 timerCount;

    REG_OS_TM1CNT_H = 0;
    delta = (s64)(alarm->fire - tick);
    OSi_EnterTimerCallback(1, OSi_AlarmHandler, 0);

    if (delta < 0) {
        timerCount = (u16)~1;
    } else if (delta < 0x10000) {
        timerCount = (u16)~delta;
    } else {
        timerCount = 0;
    }

    REG_OS_TM1CNT_L = timerCount;
    REG_OS_TM1CNT_H = 0xc1;
    OS_EnableIrqMask(16);
}