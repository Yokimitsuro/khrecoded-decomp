typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef enum SNDChannelDataShift {
    SND_CHANNEL_DATASHIFT_NONE = 0
} SNDChannelDataShift;

typedef struct NNSSndStrm {
    u8 reserved00[0x44];
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
extern u16 SND_CalcChannelVolume(int decibels);
extern void SND_SetChannelVolume(u32 channelMask, int volume,
                                 SNDChannelDataShift shift);

void NNS_SndStrmSetVolume(NNSSndStrm *stream, int volume)
{
    u16 channelVolume;
    int combinedVolume;
    int channelNumber;
    int index;

    stream->volume = volume;

    for (index = 0; index < stream->numChannels; ++index) {
        channelNumber = stream->channelNumber[index];
        combinedVolume = stream->volume + sStrmChannel[channelNumber].volume;
        channelVolume = SND_CalcChannelVolume(combinedVolume);

        SND_SetChannelVolume(1UL << channelNumber, channelVolume & 0xff,
                             (SNDChannelDataShift)(channelVolume >> 8));
    }
}