#include "libs/nitro/rtc/rtc_internal.h"

RTCResult RTC_GetTime(RTCTime *time)
{
    RTCi_Bss.work.commonResult = RTC_GetTimeAsync(time, RtcGetResultCallback, NULL);
    if (RTCi_Bss.work.commonResult == RTC_RESULT_SUCCESS) {
        RtcWaitBusy();
    }
    return RTCi_Bss.work.commonResult;
}
