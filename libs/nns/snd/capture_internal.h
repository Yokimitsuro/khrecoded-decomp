#ifndef NNS_SND_CAPTURE_INTERNAL_H
#define NNS_SND_CAPTURE_INTERNAL_H

#include "nnsys/snd.h"

typedef enum NNSSndCaptureFormat {
    NNS_SND_CAPTURE_FORMAT_PCM16,
    NNS_SND_CAPTURE_FORMAT_PCM8
} NNSSndCaptureFormat;

typedef enum NNSSndCaptureType {
    NNS_SND_CAPTURE_TYPE_REVERB,
    NNS_SND_CAPTURE_TYPE_EFFECT,
    NNS_SND_CAPTURE_TYPE_SAMPLING
} NNSSndCaptureType;

typedef void (*NNSSndCaptureCallback)(
    void *leftBuffer,
    void *rightBuffer,
    u32 length,
    NNSSndCaptureFormat format,
    void *argument);

typedef struct NNSSndCaptureState {
    BOOL active;
    NNSSndCaptureType type;
    NNSSndCaptureFormat format;
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
    NNSSndCaptureCallback callback;
    void *callbackArgument;
    NNSSndFader fader;
    BOOL fadingOut;
    int volume;
} NNSSndCaptureState;

extern volatile BOOL sSndCaptureThreadCreated;
extern NNSSndCaptureState sSndCaptureState;

#endif
