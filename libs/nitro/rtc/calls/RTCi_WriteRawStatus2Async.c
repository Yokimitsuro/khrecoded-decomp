#include "libs/nitro/rtc/rtc_internal.h"

BOOL RTCi_WriteRawStatus2Async(void)
{
    return RtcSendPxiCommand(RTC_PXI_COMMAND_WRITE_STATUS2);
}
