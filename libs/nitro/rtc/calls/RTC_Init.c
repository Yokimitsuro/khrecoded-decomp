#include "libs/nitro/rtc/rtc_internal.h"

extern void PXI_Init(void);
extern BOOL PXI_IsCallbackReady(int tag, int processor);
extern void PXI_SetFifoRecvCallback(
    int tag,
    void (*callback)(int tag, u32 data, BOOL error));

void RTC_Init(void)
{
    if (RTCi_Bss.initialized) {
        return;
    }

    RTCi_Bss.initialized = 1;
    RTCi_Bss.work.lock = RTC_LOCK_OFF;
    RTCi_Bss.work.callback = NULL;
    RTCi_Bss.work.interrupt = NULL;
    RTCi_Bss.work.buffer[0] = NULL;
    RTCi_Bss.work.buffer[1] = NULL;

    PXI_Init();
    while (!PXI_IsCallbackReady(PXI_FIFO_TAG_RTC, PXI_PROC_ARM7)) {
    }
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_RTC, RtcCommonCallback);
}
