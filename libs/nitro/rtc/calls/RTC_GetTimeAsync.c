#include "libs/nitro/rtc/rtc_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

RTCResult RTC_GetTimeAsync(RTCTime *time, RTCCallback callback, void *argument)
{
    OSIntrMode enabled;

    enabled = OS_DisableInterrupts();
    if (RTCi_Bss.work.lock != RTC_LOCK_OFF) {
        (void)OS_RestoreInterrupts(enabled);
        return RTC_RESULT_BUSY;
    }

    RTCi_Bss.work.lock = RTC_LOCK_ON;
    (void)OS_RestoreInterrupts(enabled);

    RTCi_Bss.work.sequence = RTC_SEQ_GET_TIME;
    RTCi_Bss.work.index = 0;
    RTCi_Bss.work.buffer[0] = time;
    RTCi_Bss.work.callback = callback;
    RTCi_Bss.work.callbackArg = argument;

    if (RTCi_ReadRawTimeAsync()) {
        return RTC_RESULT_SUCCESS;
    } else {
        RTCi_Bss.work.lock = RTC_LOCK_OFF;
        return RTC_RESULT_SEND_ERROR;
    }
}
