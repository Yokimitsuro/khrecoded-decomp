#include "libs/nns/snd/capture_internal.h"

#define SND_COMMAND_BLOCK (1 << 0)

extern void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
extern u32 SND_GetCurrentCommandTag(void);
extern BOOL SND_FlushCommand(u32 flags);
extern void SND_WaitForCommandProc(u32 tag);

void NNSi_SndCaptureBeginSleep(void)
{
    NNSSndCaptureState *capture = &sSndCaptureState;
    u32 commandTag;

    if (!capture->active) {
        return;
    }

    SND_StopTimer(
        capture->playingChannelMask,
        capture->captureMask,
        capture->alarmNo >= 0 ? (u32)(1 << capture->alarmNo) : 0,
        0);

    commandTag = SND_GetCurrentCommandTag();
    (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}
