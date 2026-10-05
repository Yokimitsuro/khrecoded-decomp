#ifndef NNS_SND_STRM_INTERNAL_H
#define NNS_SND_STRM_INTERNAL_H

#include "nnsys/snd.h"

typedef void (*PMSleepCallback)(void *argument);

typedef struct PMSleepCallbackInfo {
    PMSleepCallback callback;
    void *argument;
    u8 link[8];
} PMSleepCallbackInfo;

typedef enum NNSSndStrmFormat {
    NNS_SND_STRM_FORMAT_PCM8,
    NNS_SND_STRM_FORMAT_PCM16
} NNSSndStrmFormat;

typedef enum NNSSndStrmCallbackStatus {
    NNS_SND_STRM_CALLBACK_SETUP,
    NNS_SND_STRM_CALLBACK_INTERVAL
} NNSSndStrmCallbackStatus;

struct NNSSndStrm;
typedef void (*NNSSndStrmCallback)(
    NNSSndStrmCallbackStatus status,
    int channelCount,
    void *buffers[],
    u32 length,
    NNSSndStrmFormat format,
    void *argument);

typedef struct NNSSndStrm {
    NNSFndLink link;
    PMSleepCallbackInfo preSleepInfo;
    PMSleepCallbackInfo postSleepInfo;
    NNSSndStrmFormat format;
    BOOL activeFlag : 1;
    BOOL startFlag : 1;
    u32 reservedFlags : 30;
    u32 channelBufferLength;
    int interval;
    NNSSndStrmCallback callback;
    void *callbackArgument;
    int currentBuffer;
    int volume;
    int alarmNo;
    u32 channelMask;
    int channelCount;
    u8 channelNo[16];
} NNSSndStrm;

typedef struct NNSSndStrmChannel {
    void *buffer;
    int volume;
} NNSSndStrmChannel;

extern BOOL sSndStrmInitialized;
extern NNSFndList sSndStrmList;
extern NNSSndStrmChannel sStrmChannel[16];

#endif
