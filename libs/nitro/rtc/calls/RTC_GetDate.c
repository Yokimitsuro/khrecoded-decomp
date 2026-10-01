#include "libs/nitro/rtc/rtc_internal.h"

RTCResult RTC_GetDate(RTCDate *date)
{
    RTCi_Bss.work.commonResult = RTC_GetDateAsync(date, RtcGetResultCallback, NULL);
    if (RTCi_Bss.work.commonResult == RTC_RESULT_SUCCESS) {
        RtcWaitBusy();
    }
    return RTCi_Bss.work.commonResult;
}
