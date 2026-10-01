typedef unsigned int u32;

typedef struct NNSSndStrm {
    unsigned char padding00[0x4c];
    u32 channelMask;
    int channelCount;
} NNSSndStrm;

extern void NNS_SndUnlockChannel(u32 channelMask);

void NNS_SndStrmFreeChannel(NNSSndStrm *stream)
{
    if (stream->channelMask == 0) {
        return;
    }

    NNS_SndUnlockChannel(stream->channelMask);
    stream->channelMask = 0;
    stream->channelCount = 0;
}
