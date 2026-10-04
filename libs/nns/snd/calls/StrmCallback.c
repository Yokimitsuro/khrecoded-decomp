typedef unsigned char u8;
typedef unsigned long u32;

typedef enum NNSSndStrmFormat {
    NNS_SND_STRM_FORMAT_PCM8,
    NNS_SND_STRM_FORMAT_PCM16
} NNSSndStrmFormat;

typedef enum NNSSndStrmCallbackStatus {
    NNS_SND_STRM_CALLBACK_SETUP,
    NNS_SND_STRM_CALLBACK_INTERVAL
} NNSSndStrmCallbackStatus;

typedef void (*NNSSndStrmCallback)(NNSSndStrmCallbackStatus status,
                                   int numChannels, void **buffers, u32 length,
                                   NNSSndStrmFormat format, void *argument);

typedef struct NNSSndStrm {
    u8 reserved00[0x28];
    NNSSndStrmFormat format;
    u32 flags;
    u32 channelBufferLength;
    int interval;
    NNSSndStrmCallback callback;
    void *callbackArgument;
    int currentBuffer;
    int volume;
    int alarmNumber;
    u32 channelBitMask;
    int numChannels;
    u8 channelNumber[16];
} NNSSndStrm;

typedef struct NNSSndStrmChannel {
    void *buffer;
    int volume;
} NNSSndStrmChannel;

extern NNSSndStrmChannel sStrmChannel[16];
extern void *data_0205e188[16];

void StrmCallback(NNSSndStrm *stream, NNSSndStrmCallbackStatus status)
{
    const unsigned long blockSize = stream->channelBufferLength / stream->interval;
    const unsigned long offset = blockSize * stream->currentBuffer;
    int index;
    int channelNumber;

    for (index = 0; index < stream->numChannels; index++) {
        channelNumber = stream->channelNumber[index];
        data_0205e188[index] = (u8 *)(sStrmChannel[channelNumber].buffer) + offset;
    }

    stream->callback(status, stream->numChannels, data_0205e188, blockSize,
                     stream->format, stream->callbackArgument);

    stream->currentBuffer++;
    if (stream->currentBuffer >= stream->interval) stream->currentBuffer = 0;
}