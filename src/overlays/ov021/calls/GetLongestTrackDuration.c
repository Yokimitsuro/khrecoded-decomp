#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    s32 duration;
    u8 pad_14[0xe];
    u8 state : 3;
    u8 stateHigh : 5;
    u8 pad_23[0x31];
} AnimTrack;

typedef struct {
    u8 pad_00[0x42];
    s16 trackCount;
    AnimTrack *tracks;
} AnimSet;

s32 GetLongestTrackDuration(AnimSet *set)
{

    s32 longest = 0;
    s32 i = 0;

    for (; i < set->trackCount; i++) {
        AnimTrack *track = &set->tracks[i];
        if (track->state != 2) {
            if (longest < track->duration) {
                longest = track->duration;
            }
        } else {
            longest = 0x7fffffff;
            break;
        }
    }
    return longest;
}
