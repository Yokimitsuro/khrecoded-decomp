typedef unsigned int u32;

typedef struct NNSSndStrm {
    unsigned char reserved0[8];
    unsigned char preSleepInfo[0x10];
    unsigned char postSleepInfo[0x14];
    int reservedFlag : 1;
    int startFlag : 1;
    int remainingFlags : 30;
    unsigned char reserved1[0x18];
    int alarmNo;
    u32 channelBitMask;
} NNSSndStrm;

extern void SND_StartTimer(u32 channelBitMask, u32 captureBitMask, u32 alarmBitMask, u32 flags);
extern void PM_PrependPreSleepCallback(void *info);
extern void PM_AppendPostSleepCallback(void *info);

void NNS_SndStrmStart(NNSSndStrm *stream)
{
    SND_StartTimer(stream->channelBitMask, 0, 1 << stream->alarmNo, 0);
    if (!stream->startFlag) {
        PM_PrependPreSleepCallback(&stream->preSleepInfo);
        PM_AppendPostSleepCallback(&stream->postSleepInfo);
        stream->startFlag = 1;
    }
}