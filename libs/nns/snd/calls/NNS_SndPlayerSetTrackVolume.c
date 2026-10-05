#include "nnsys/snd.h"

extern const s16 data_02052b1c[128];
extern void SND_SetTrackParam0A(int playerNo, u32 trackMask, int volume);

static inline s16 SND_CalcDecibel(int volume)
{
    return data_02052b1c[volume];
}

void NNS_SndPlayerSetTrackVolume(NNSSndHandle *handle, u16 trackMask, int volume)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    SND_SetTrackParam0A(
        handle->player->playerNo,
        trackMask,
        SND_CalcDecibel(volume));
}
