#include "libs/nitro/rtc/rtc_internal.h"

BOOL RTCi_ReadRawTimeAsync(void)
{
    return RtcSendPxiCommand(RTC_PXI_COMMAND_READ_TIME);
}
