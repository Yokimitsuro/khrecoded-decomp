#include "libs/nitro/os/os_alarm_internal.h"

void OS_CreateAlarm(OSAlarm *alarm)
{
    alarm->handler = 0;
    alarm->tag = 0;
}