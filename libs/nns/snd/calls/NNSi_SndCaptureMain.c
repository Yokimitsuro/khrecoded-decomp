#include "libs/nns/snd/capture_internal.h"

extern void SND_SetChannelVolume(u32 channelMask, int volume, int shift);
extern int NNSi_SndFaderGet(const NNSSndFader *fader);
extern void NNSi_SndFaderUpdate(NNSSndFader *fader);
extern BOOL NNSi_SndFaderIsFinished(const NNSSndFader *fader);
extern void NNSi_SndCaptureStop(void);

void NNSi_SndCaptureMain(void)
{
    NNSSndCaptureState *capture = &sSndCaptureState;
    NNSSndFader *fader;
    int volume;

    if (capture->active && capture->type == NNS_SND_CAPTURE_TYPE_REVERB) {
        fader = &capture->fader;
        NNSi_SndFaderUpdate(fader);

        if (capture->fadingOut && NNSi_SndFaderIsFinished(fader)) {
            NNSi_SndCaptureStop();
            return;
        }

        volume = NNSi_SndFaderGet(fader) >> 8;
        if (volume != capture->volume) {
            SND_SetChannelVolume(capture->playingChannelMask, volume, 0);
            capture->volume = volume;
        }
    }
}
