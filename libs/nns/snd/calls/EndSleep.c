typedef unsigned char u8;
typedef unsigned int u32;
typedef int OSIntrMode;
typedef struct NNSSndStrm {
    u8 reserved0[0x2c];
    int activeFlag : 1;
    int startFlag : 1;
    int remainingFlags : 30;
    u8 reserved1[0x10];
    int curBuffer;
    u8 reserved2[4];
    int alarmNo;
    u32 channelBitMask;
} NNSSndStrm;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void StrmCallback(NNSSndStrm *stream, int status);
extern void SND_StartTimer(u32 channelBitMask, u32 captureBitMask, u32 alarmBitMask, u32 flags);
void EndSleep(void *arg)
{
    NNSSndStrm *stream = (NNSSndStrm *)arg;
    if (!stream->startFlag) return;
    while (stream->curBuffer != 0) {
        OSIntrMode old = OS_DisableInterrupts();
        StrmCallback(stream, 1);
        (void)OS_RestoreInterrupts(old);
    }
    SND_StartTimer(stream->channelBitMask, 0, 1 << stream->alarmNo, 0);
}