typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

#define TICKS_PER_FRAME_NUMERATOR 0x000007fd88400000ULL

struct MobiClipFrameTimer {
    void *pDecoder;
    u8 alarm[0x2c];
    s64 nStartTick;
    u8 nState;
    u8 nFrontBuffer;
    u8 bPrimed;
    u8 pad003b;
    u32 pad003c;
    int nDecoded;
    u32 nConsumed;
    int nPresented;
    u64 nTimeBase;
    int (*pfnBufferForIndex)(int nIndex);
};

extern void func_ov022_020a937c(void *pDecoder);
extern void func_ov022_020a9358(void *pDecoder, int nValue, int nCount, int nFlags);
extern void movie_frame_alarm_callback(struct MobiClipFrameTimer *frameTimer);
extern s64 OS_GetTick(void);
extern void OS_SetAlarm(void *pAlarm, u64 nTick, void *pfnHandler, void *pArg);

void movie_frame_alarm_callback(struct MobiClipFrameTimer *frameTimer)
{
    int decodedAhead = frameTimer->nDecoded - (int)frameTimer->nConsumed;
    s64 elapsedTicks;
    u64 nextDeadline;

    if (decodedAhead > 0) {
        if (decodedAhead <= 3 && frameTimer->nState < 4) {
            func_ov022_020a937c(frameTimer->pDecoder);
        } else if (frameTimer->bPrimed == 0) {
            OS_SetAlarm(frameTimer->alarm, 1, (void *)&movie_frame_alarm_callback, frameTimer);
            return;
        } else {
            func_ov022_020a9358(frameTimer->pDecoder,
                                frameTimer->pfnBufferForIndex((signed char)frameTimer->nFrontBuffer),
                                0x100, 0);
            frameTimer->bPrimed = 0;
        }
    } else if (frameTimer->bPrimed == 0) {
        OS_SetAlarm(frameTimer->alarm, 1, (void *)&movie_frame_alarm_callback, frameTimer);
        return;
    } else {
        frameTimer->bPrimed = 0;
    }

    frameTimer->nConsumed++;
    elapsedTicks = OS_GetTick() - frameTimer->nStartTick;
    nextDeadline = (frameTimer->nConsumed + 1) * TICKS_PER_FRAME_NUMERATOR / frameTimer->nTimeBase;
    OS_SetAlarm(frameTimer->alarm, nextDeadline - elapsedTicks,
                (void *)&movie_frame_alarm_callback, frameTimer);
}
