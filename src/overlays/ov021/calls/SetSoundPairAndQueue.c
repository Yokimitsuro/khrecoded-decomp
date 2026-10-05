#include "nitro/types.h"

typedef struct SoundPair {
    u8 pad_00[0x28];
    int first;
    int second;
} SoundPair;

extern void QueueSoundCommandForArc(int soundId);

void SetSoundPairAndQueue(SoundPair *pair, int first, int second)
{
    pair->first = first;
    QueueSoundCommandForArc(first);
    if (second >= 0) {
        pair->second = second;
        QueueSoundCommandForArc(second);
    }
}
