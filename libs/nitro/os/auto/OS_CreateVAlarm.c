#include "libs/nitro/os/os_valarm_internal.h"

void OS_CreateVAlarm(OSVAlarm *alarm)
{
    alarm->handler = 0;
    alarm->tag = 0;
    alarm->finish = 0;
}
