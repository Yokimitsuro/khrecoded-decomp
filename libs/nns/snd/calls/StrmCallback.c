typedef unsigned char u8;
typedef unsigned long u32;
typedef enum NNSSndStrmFormat { NNS_SND_STRM_FORMAT_PCM8, NNS_SND_STRM_FORMAT_PCM16 } NNSSndStrmFormat;
typedef enum NNSSndStrmCallbackStatus { NNS_SND_STRM_CALLBACK_SETUP, NNS_SND_STRM_CALLBACK_INTERVAL } NNSSndStrmCallbackStatus;
typedef void (*NNSSndStrmCallback)(NNSSndStrmCallbackStatus, int, void **, u32, NNSSndStrmFormat, void *);
typedef struct NNSSndStrm {
    u8 reserved00[0x28];
    NNSSndStrmFormat format;
    u32 flags;
    u32 chBufLen;
    int interval;
    NNSSndStrmCallback callback;
    void *callbackArg;
    int curBuffer;
    int volume;
    int alarmNo;
    u32 chBitMask;
    int numChannels;
    u8 channelNo[16];
} NNSSndStrm;
typedef struct NNSSndStrmChannel { void *buffer; int volume; } NNSSndStrmChannel;
extern NNSSndStrmChannel data_0205e1c8[16];
extern void *data_0205e188[16];
void StrmCallback(NNSSndStrm *stream, NNSSndStrmCallbackStatus status)
{
    const unsigned long blockSize = stream->chBufLen / stream->interval;
    const unsigned long offset = blockSize * stream->curBuffer;
    int index;
    int chNo;

    for (index = 0; index < stream->numChannels; index++) {
        chNo = stream->channelNo[index];
        data_0205e188[index] = (u8 *)(data_0205e1c8[chNo].buffer) + offset;
    }

    stream->callback(status, stream->numChannels, data_0205e188, blockSize, stream->format, stream->callbackArg);

    stream->curBuffer++;
    if (stream->curBuffer >= stream->interval) stream->curBuffer = 0;
}