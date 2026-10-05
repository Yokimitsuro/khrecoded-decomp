#include "nitro/types.h"

typedef struct ActorSoundTrack {
    s32 timer;
    u8 pad_04[0x54];
} ActorSoundTrack;

typedef struct Actor {
    u8 pad_000[0x8e4];
    ActorSoundTrack tracks[4];
} Actor;

extern u32 GetPanelFieldB8(void);
extern void PlayActorBodySound(Actor *actor, int trackIndex);

void Actor_FireExpiredTrackCues(Actor *actor)
{
    int trackIndex;

    if (GetPanelFieldB8() != 0) {
        return;
    }
    for (trackIndex = 1; trackIndex < 4; trackIndex++) {
        if (actor->tracks[trackIndex].timer >= 0xcd) {
            PlayActorBodySound(actor, trackIndex);
        }
    }
}
