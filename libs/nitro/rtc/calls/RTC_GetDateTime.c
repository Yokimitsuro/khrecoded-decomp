#include "libs/nitro/rtc/rtc_internal.h"

RTCResult RTC_GetDateTime(RTCDate *date, RTCTime *time)
{
    RTCi_Bss.work.commonResult =
        RTC_GetDateTimeAsync(date, time, RtcGetResultCallback, NULL);
    if (RTCi_Bss.work.commonResult == RTC_RESULT_SUCCESS) {
        RtcWaitBusy();
    }
    return RTCi_Bss.work.commonResult;
}
