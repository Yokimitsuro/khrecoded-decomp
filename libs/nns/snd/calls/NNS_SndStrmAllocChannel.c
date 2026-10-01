typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSSndStrm {
    unsigned char reserved[0x4c];
    u32 channelBitMask;
    int numChannels;
    u8 channelNo[16];
} NNSSndStrm;

extern BOOL NNS_SndLockChannel(u32 channelBitMask);

BOOL NNS_SndStrmAllocChannel(NNSSndStrm *stream, int numChannels, const u8 channelList[])
{
    u32 channelBitMask = 0;
    int i;

    for (i = 0; i < numChannels; i++) {
        int channel = channelList[i];
        stream->channelNo[i] = channel;
        channelBitMask |= 1 << channel;
    }
    if (!NNS_SndLockChannel(channelBitMask)) {
        return 0;
    }
    stream->numChannels = numChannels;
    stream->channelBitMask = channelBitMask;
    return 1;
}