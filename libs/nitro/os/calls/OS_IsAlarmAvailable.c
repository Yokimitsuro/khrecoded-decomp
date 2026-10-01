#include "libs/nitro/os/os_alarm_internal.h"

BOOL OS_IsAlarmAvailable(void)
{
    return OSi_AlarmState.useAlarm;
}