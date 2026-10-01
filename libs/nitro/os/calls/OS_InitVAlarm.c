#include "libs/nitro/os/os_valarm_internal.h"

extern u32 OS_DisableIrqMask(u32 mask);

void OS_InitVAlarm(void)
{
    if (!OSi_VAlarmState.enabled) {
        OSi_VAlarmState.enabled = 1;
        OSi_VAlarmState.head = 0;
        OSi_VAlarmState.tail = 0;
        OS_DisableIrqMask(4);
        OSi_VAlarmState.frameCount = 0;
        OSi_VAlarmState.previousVCount = 0;
    }
}