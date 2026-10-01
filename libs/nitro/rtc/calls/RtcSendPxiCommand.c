#include "libs/nitro/rtc/rtc_internal.h"

extern int PXI_SendWordByFifo(int tag, u32 data, BOOL error);

BOOL RtcSendPxiCommand(u32 command)
{
    if (PXI_SendWordByFifo(
            PXI_FIFO_TAG_RTC,
            (command << RTC_PXI_COMMAND_SHIFT) & RTC_PXI_COMMAND_MASK,
            FALSE) < 0) {
        return FALSE;
    }
    return TRUE;
}
