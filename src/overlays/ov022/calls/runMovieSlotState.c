typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

#define QUEUE_DEPTH 10

struct MobiClipAudioStream {
    void *pStream;
    short *pLeft;
    short *pRight;
    int pad000c;
    u32 nSampleRate;
    u32 nFrameSamples;
    u32 nChannels;
    int nFilled;
    u32 nBlocks;
};

struct MobiClipFrameTimer {
    void *pStream;
    u8 alarm[0x2c];
    s64 nStartTick;
    u8 nState;
    u8 nFrontBuffer;
    u8 bPresented;
    u8 pad003b[0x40 - 0x3b];
    u32 nDecoded;
    u32 nConsumed;
    int nPresented;
    u64 nTimeBase;
    void *pfnBufferForIndex;
};

struct MobiClipGlobals {
    u8 bStopped;
    u8 pad0001[3];
    struct MobiClipAudioStream *pAudio;
    struct MobiClipFrameTimer *pMain;
    struct MobiClipFrameTimer *pSub;
};

extern struct MobiClipGlobals data_ov022_020b7da8;
extern int data_ov022_020b7db4;

extern s64 OS_GetTick(void);
extern void OS_SetAlarm(void *pAlarm, u64 nTick, void *pfnHandler, void *pArg);
extern void SND_SetChannelVolume(u32 nChannelMask, int nVolume, int nShift);
extern void SND_FlushCommand(int nChannel);
extern void OS_CancelAlarm(void *pAlarm);
extern void startStereoPcmStream(struct MobiClipAudioStream *pAudio);
extern int func_ov022_020a9310(void *pStream);
extern void func_ov022_020a809c(struct MobiClipFrameTimer *pTimer);
extern void flushPendingStereoAudioBlocks(struct MobiClipAudioStream *pAudio);
extern void movie_frame_alarm_callback(struct MobiClipFrameTimer *pTimer);

int runMovieSlotState(struct MobiClipFrameTimer *pTimer)
{
    struct MobiClipAudioStream *pAudio;
    int bOwnsAudio;
    int nState;

    if (pTimer == 0) {
        return 1;
    }

    bOwnsAudio = 0;
    pAudio = data_ov022_020b7da8.pAudio;
    if (pAudio != 0 && pAudio->pStream == pTimer->pStream) {
        bOwnsAudio = 1;
    }
    nState = pTimer->nState;
    if (bOwnsAudio == 0) {
        pAudio = 0;
    }

    switch (nState) {
    case 0:
        return 0;

    case 1:
        pTimer->nStartTick = OS_GetTick();
        if (pAudio != 0) {
            startStereoPcmStream(pAudio);
        }
        pTimer->nState = 2;
        OS_SetAlarm(pTimer->alarm, 0, (void *)&movie_frame_alarm_callback, pTimer);

    case 2:
        if (func_ov022_020a9310(pTimer->pStream) == 0
            || ((int *)&data_ov022_020b7db4)[0x16] != 0) {
            if (pAudio != 0) {
                SND_SetChannelVolume(3, 0, 0);
                SND_FlushCommand(1);
            }
            pTimer->nState = 4;
            return 0;
        }
        pTimer->nState = 3;

    case 3:
        if (pTimer->nDecoded - pTimer->nConsumed < QUEUE_DEPTH) {
            func_ov022_020a809c(pTimer);
            if (pAudio != 0) {
                flushPendingStereoAudioBlocks(pAudio);
            }
            pTimer->nState = 2;
        }
        return 0;

    case 4:
        if (pTimer->nDecoded <= pTimer->nConsumed) {
            pTimer->nState = 5;
        }
        return 0;

    case 5:
        if (pTimer->bPresented != 0) {
            return 0;
        }
        pTimer->nState = 6;
        OS_CancelAlarm(pTimer->alarm);
        return 1;
    }
    return 1;
}
