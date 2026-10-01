#include "libs/nitro/rtc/rtc_internal.h"

void RtcGetResultCallback(RTCResult result, void *argument)
{
    RTCi_Bss.work.commonResult = result;
}
