#include "libs/nns/snd/capture_internal.h"

#define SND_COMMAND_BLOCK (1 << 0)
#define OS_MESSAGE_NOBLOCK 0

typedef void *OSMessage;
typedef struct OSMessageQueue OSMessageQueue;

extern OSMessageQueue sSndCaptureMessageQueue;
extern void SND_StopTimer(u32 channelMask, u32 captureMask, u32 alarmMask, u32 flags);
extern u32 SND_GetCurrentCommandTag(void);
extern BOOL SND_FlushCommand(u32 flags);
extern void SND_WaitForCommandProc(u32 tag);
extern BOOL OS_ReceiveMessage(OSMessageQueue *queue, OSMessage *message, s32 flags);
extern void NNS_SndUnlockCapture(u32 captureMask);
extern void NNS_SndUnlockChannel(u32 channelMask);
extern void SND_ClearChannelBit(int alarmNo);
extern void SND_SetOutputSelector(int left, int right, int channel1, int channel3);

void NNSi_SndCaptureStop(void)
{
    NNSSndCaptureState *capture = &sSndCaptureState;
    u32 commandTag;
    BOOL usesAlarm;

    if (!capture->active) {
        return;
    }

    usesAlarm = capture->alarmNo >= 0 ? TRUE : FALSE;
    SND_StopTimer(
        capture->playingChannelMask,
        capture->captureMask,
        usesAlarm ? (u32)(1 << capture->alarmNo) : 0,
        0);

    if (usesAlarm) {
        commandTag = SND_GetCurrentCommandTag();
        (void)SND_FlushCommand(SND_COMMAND_BLOCK);
        SND_WaitForCommandProc(commandTag);
        while (OS_ReceiveMessage(
            &sSndCaptureMessageQueue, NULL, OS_MESSAGE_NOBLOCK)) {
        }
    }

    if (capture->captureMask != 0) {
        NNS_SndUnlockCapture(capture->captureMask);
    }
    if (capture->channelMask != 0) {
        NNS_SndUnlockChannel(capture->channelMask);
    }
    if (usesAlarm) {
        SND_ClearChannelBit(capture->alarmNo);
    }

    if (capture->type == NNS_SND_CAPTURE_TYPE_EFFECT) {
        SND_SetOutputSelector(0, 0, 0, 0);
    }
    capture->active = FALSE;
}
