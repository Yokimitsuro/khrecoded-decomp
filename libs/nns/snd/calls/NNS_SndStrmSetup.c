#include "libs/nns/snd/strm_internal.h"

typedef int OSIntrMode;

enum {
    SND_CHANNEL_LOOP_REPEAT = 1,
    SND_CHANNEL_DATASHIFT_NONE = 0
};

extern void NNS_SndStrmStop(NNSSndStrm *stream);
extern int NNS_SndAllocAlarm(void);
extern u32 _u32_div_f(u32 dividend, u32 divisor);
extern void SND_SetupChannelPcm(
    int channelNo,
    int format,
    const void *data,
    int loop,
    int loopStart,
    int dataLength,
    int volume,
    int dataShift,
    int timer,
    int pan);
extern void SND_SetupAlarm(
    int alarmNo,
    u32 tick,
    u32 period,
    void (*handler)(void *argument),
    void *argument);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void AlarmCallback(void *argument);
extern void StrmCallback(NNSSndStrm *stream, NNSSndStrmCallbackStatus status);
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

BOOL NNS_SndStrmSetup(
    NNSSndStrm *stream,
    NNSSndStrmFormat format,
    void *buffer,
    u32 bufferSize,
    int timer,
    int interval,
    NNSSndStrmCallback callback,
    void *argument)
{
    NNSSndStrmChannel *channel;
    u32 samples;
    u32 alarmTimer;
    int channelNo;
    int index;

    if (stream->activeFlag) {
        NNS_SndStrmStop(stream);
    }

    bufferSize = _u32_div_f(
        bufferSize,
        32 * interval * stream->channelCount);
    stream->channelBufferLength = bufferSize * interval * 32;

    samples = stream->channelBufferLength;
    if (format == NNS_SND_STRM_FORMAT_PCM16) {
        samples >>= 1;
    }
    alarmTimer = _u32_div_f(timer * samples, interval);

    stream->alarmNo = NNS_SndAllocAlarm();
    if (stream->alarmNo < 0) {
        return FALSE;
    }

    for (index = 0; index < stream->channelCount; index++) {
        channelNo = stream->channelNo[index];
        channel = &sStrmChannel[channelNo];
        channel->buffer = (u8 *)buffer + stream->channelBufferLength * index;
        channel->volume = 0;

        SND_SetupChannelPcm(
            channelNo,
            (int)format,
            channel->buffer,
            SND_CHANNEL_LOOP_REPEAT,
            0,
            (int)(stream->channelBufferLength >> 2),
            127,
            SND_CHANNEL_DATASHIFT_NONE,
            timer << 5,
            64);
    }

    SND_SetupAlarm(
        stream->alarmNo,
        alarmTimer,
        alarmTimer,
        AlarmCallback,
        stream);
    NNS_FndAppendListObject(&sSndStrmList, stream);

    stream->format = format;
    stream->interval = interval;
    stream->callback = callback;
    stream->callbackArgument = argument;
    stream->currentBuffer = 0;
    stream->volume = 0;
    stream->activeFlag = TRUE;

    {
        OSIntrMode oldInterrupts = OS_DisableInterrupts();
        stream->interval = 1;
        StrmCallback(stream, NNS_SND_STRM_CALLBACK_SETUP);
        stream->interval = interval;
        (void)OS_RestoreInterrupts(oldInterrupts);
    }

    return TRUE;
}
