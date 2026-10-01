typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef struct NNSSndStrm {
    u8 reserved0[0x2c];
    int activeFlag : 1;
    int startFlag : 1;
    int remainingFlags : 30;
    u8 reserved1[0x18];
    int alarmNo;
    u32 channelBitMask;
} NNSSndStrm;
extern void SND_StopTimer(u32 channelBitMask, u32 captureBitMask, u32 alarmBitMask, u32 flags);
extern u32 SND_GetCurrentCommandTag(void);
extern BOOL SND_FlushCommand(u32 flags);
extern void SND_WaitForCommandProc(u32 tag);
void BeginSleep_2(void *arg)
{
    NNSSndStrm *stream = (NNSSndStrm *)arg;
    u32 commandTag;
    if (!stream->startFlag) return;
    SND_StopTimer(stream->channelBitMask, 0, 1 << stream->alarmNo, 0);
    commandTag = SND_GetCurrentCommandTag();
    (void)SND_FlushCommand(1);
    SND_WaitForCommandProc(commandTag);
}