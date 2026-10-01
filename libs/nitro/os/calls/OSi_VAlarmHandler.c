#include "libs/nitro/os/os_valarm_internal.h"

extern u32 SDK_AUTOLOAD_DTCM_START;
extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_ResetRequestIrqMask(u32 mask);

static inline void SetVCountInterrupt(BOOL enabled)
{
    volatile u16 *dispstat = (volatile u16 *)0x04000004;

    if (enabled) {
        *dispstat |= 0x20;
    } else {
        *dispstat &= 0xffdf;
    }
}

static inline s32 GetVCount(void)
{
    return *(volatile u16 *)0x04000006;
}

static inline s32 GetVCountCompare(void)
{
    u16 value = *(volatile u16 *)0x04000004;
    return ((value >> 8) & 0xff) | ((value << 1) & 0x100);
}

void OSi_VAlarmHandler(void *arg)
{
    OSVAlarm *alarm;
    OSVAlarmHandler handler;
    int check;
    s32 currentVCount;
    s32 currentVFrame;

    OS_DisableIrqMask(4);
    SetVCountInterrupt(0);
    *(volatile u32 *)((u8 *)&SDK_AUTOLOAD_DTCM_START + 0x3ff8) |= 4;

    currentVCount = GetVCountCompare();
    currentVFrame = OSi_GetVFrame(currentVCount - 1);

    while ((alarm = OSi_VAlarmState.head) != 0) {
        currentVCount = GetVCount();
        currentVFrame = OSi_GetVFrame(currentVCount);
        check = OSi_CompareVCount(alarm, currentVFrame, currentVCount);

        switch (check) {
        case 0:
            OSi_SetNextVAlarm(alarm);
            if (alarm->fire != GetVCount() || alarm->frame != currentVFrame) {
                return;
            }
            OS_DisableIrqMask(4);
            SetVCountInterrupt(0);
            OS_ResetRequestIrqMask(4);
        case 1:
            handler = alarm->handler;
            OSi_DetachVAlarm(alarm);
            alarm->handler = 0;
            if (handler) {
                handler(alarm->arg);
            }
            if (alarm->period && !alarm->canceled) {
                alarm->handler = handler;
                alarm->frame = (u32)OSi_VAlarmState.frameCount + 1;
                OSi_InsertVAlarm(alarm);
            }
            break;
        case 2:
            OSi_DetachVAlarm(alarm);
            alarm->frame = (u32)OSi_VAlarmState.frameCount + 1;
            OSi_InsertVAlarm(alarm);
            break;
        }
    }
}