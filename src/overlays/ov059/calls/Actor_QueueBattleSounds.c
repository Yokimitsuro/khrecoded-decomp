#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x998];
    u8 soundPair[8];
} Actor;

extern void SetSoundPairAndQueue(void *pair, int first, int second);
extern void QueueSoundCommandForArc(int soundId);

void Actor_QueueBattleSounds(Actor *actor)
{
    SetSoundPairAndQueue(actor->soundPair, 0x30, 0x48);
    QueueSoundCommandForArc(0xca);
    QueueSoundCommandForArc(0xcb);
    QueueSoundCommandForArc(0xcc);
    QueueSoundCommandForArc(0xcd);
}
