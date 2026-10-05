#include "nitro/types.h"

typedef struct SoundOwner {
    u8 pad_00[0x34];
    int soundId;
} SoundOwner;

extern void QueueSoundCommandForArc(int soundId);

void SetSoundIdAndQueue(SoundOwner *owner, int soundId)
{
    owner->soundId = soundId;
    if (soundId >= 0) {
        QueueSoundCommandForArc(soundId);
    }
}
