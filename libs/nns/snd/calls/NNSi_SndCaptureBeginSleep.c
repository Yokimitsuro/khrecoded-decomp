#include "nitro/types.h"

#define SND_COMMAND_BLOCK (1 << 0)

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

typedef struct NNSSndCaptureState {
    BOOL active;
    int type;
    int format;
    void *leftBuffer;
    void *rightBuffer;
    u32 bufferLength;
    u32 blockSize;
    int currentBuffer;
    u32 channelMask;
    u32 playingChannelMask;
    u32 captureMask;
    int alarmNo;
    int interval;
    void (*callback)(void);
    void *callbackArgument;
    NNSSndFader fader;
    BOOL fadingOut;
    int volume;
} NNSSndCaptureState;

extern NNSSndCaptureState data_0205e290;
extern void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
extern u32 SND_GetCurrentCommandTag(void);
extern BOOL SND_FlushCommand(u32 flags);
extern void SND_WaitForCommandProc(u32 tag);

void NNSi_SndCaptureBeginSleep(void)
{
    NNSSndCaptureState *capture = &data_0205e290;
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
