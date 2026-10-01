typedef struct NNSSndStrm {
    unsigned char padding00[0x50];
    int channelCount;
    unsigned char channelNumber[16];
} NNSSndStrm;

extern void SND_SetChannelPan(unsigned int channelMask, int pan);

void NNS_SndStrmSetChannelPan(NNSSndStrm *stream, int channel, int pan)
{
    if (channel > stream->channelCount - 1) {
        return;
    }

    SND_SetChannelPan(1U << stream->channelNumber[channel], pan);
}
