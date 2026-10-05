#include "nitro/types.h"

#define SND_COMMAND_BLOCK (1 << 0)

extern BOOL SND_FlushCommand(u32 flags);
extern void SND_WaitForCommandProc(u32 tag);
extern u32 SND_GetCurrentCommandTag(void);
extern void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
extern void NNSi_SndCaptureBeginSleep(void);

void BeginSleep(void *)
{
    u32 commandTag;

    NNSi_SndCaptureBeginSleep();
    SND_StopTimer(0, 0, 0, 0);

    commandTag = SND_GetCurrentCommandTag();
    (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}
