typedef struct SNDVoiceChannel {
    unsigned char reserved[0x118];
    int flags;
    unsigned char faderPadding[0x3c];
    int finishCallback;
} SNDVoiceChannel;

extern void ForceStopStrm_2(SNDVoiceChannel *channel);
extern void NNSi_SndFaderSet(void *fader, int target, int frames);

void SNDi_FreeVoiceChannel(SNDVoiceChannel *channel, int fadeFrames)
{
    if (((channel->flags << 30) >> 31) == 0) {
        ForceStopStrm_2(channel);
        return;
    }
    if (fadeFrames == 0) {
        ForceStopStrm_2(channel);
        return;
    }
    NNSi_SndFaderSet((char *)channel + 0xf0, 0, fadeFrames);
    channel->flags |= 8;
    channel->finishCallback = 0;
}
