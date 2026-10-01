#include "libs/nitro/rtc/rtc_internal.h"

asm void RtcWaitBusy(void)
{
    ldr r12, =RTCi_Lock
loop:
    ldr r0, [r12, #0]
    cmp r0, #RTC_LOCK_ON
    beq loop
    bx lr
}
