#include "libs/nitro/os/os_valarm_internal.h"

extern void OS_SetIrqFunction(u32 mask, void (*function)(void));
extern void GX_SetVCountEqVal(s16 vcount);
extern u32 OS_EnableIrqMask(u32 mask);
extern void OSi_VAlarmHandler(void);

void OSi_SetNextVAlarm(OSVAlarm *alarm)
{
    OS_SetIrqFunction(4, OSi_VAlarmHandler);
    GX_SetVCountEqVal(alarm->fire);
    *(volatile u16 *)0x04000004 |= 0x20;
    OS_EnableIrqMask(4);
}