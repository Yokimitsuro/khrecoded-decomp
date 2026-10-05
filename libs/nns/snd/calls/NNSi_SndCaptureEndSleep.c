#include "libs/nns/snd/capture_internal.h"

extern void MIi_CpuClear32(u32 value, void *destination, u32 size);
extern void DC_FlushRange(const void *startAddress, u32 size);
extern void SND_StartTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);

static inline void MI_CpuClear32(void *destination, u32 size)
{
    MIi_CpuClear32(0, destination, size);
}

void NNSi_SndCaptureEndSleep(void)
{
    NNSSndCaptureState *capture = &sSndCaptureState;

    if (!capture->active) {
        return;
    }

    capture->currentBuffer = 0;
    MI_CpuClear32(capture->leftBuffer, capture->bufferLength);
    MI_CpuClear32(capture->rightBuffer, capture->bufferLength);
    DC_FlushRange(capture->leftBuffer, capture->bufferLength);
    DC_FlushRange(capture->rightBuffer, capture->bufferLength);
    SND_StartTimer(
        capture->playingChannelMask,
        capture->captureMask,
        capture->alarmNo >= 0 ? (u32)(1 << capture->alarmNo) : 0,
        0);
}
