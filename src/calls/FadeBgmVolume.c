#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00000[0xb44d8];
    NNSSndHandle bgmHandle;
    u8 pad_b44dc[0xb472f - 0xb44dc];
    u8 bgmVolume;
} SoundWork;

extern SoundWork *gSoundWork;
extern void NNS_SndPlayerMoveVolume(NNSSndHandle *handle, int targetVolume, int frames);

void FadeBgmVolume(int targetVolume, int frames)
{
    NNS_SndPlayerMoveVolume(&gSoundWork->bgmHandle, targetVolume, frames);
    gSoundWork->bgmVolume = targetVolume;
}
