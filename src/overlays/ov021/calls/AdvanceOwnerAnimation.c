#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 flags;
    s16 frames[5];
    void *anims[5];
} AnimTrackSet;

typedef struct {
    u8 pad_00[0x30];
    AnimTrackSet tracks;
} AnimOwner;

extern fx32 func_0202f4cc(AnimTrackSet *tracks, u16 index);
extern u16 AdvanceAnimationTracks(AnimTrackSet *tracks, fx32 delta);

s16 AdvanceOwnerAnimation(AnimOwner *owner, fx32 step)
{
    int result = 1;
    AnimTrackSet *tracks = &owner->tracks;
    fx32 length = 0;
    int i;

    for (i = 0; i < 5; i++) {
        if (tracks->anims[i] != NULL && tracks->frames[i] >= 0) {
            length = func_0202f4cc(tracks, i);
            break;
        }
    }
    if (length >= step) {
        result = AdvanceAnimationTracks(tracks, step);
    }
    return (s16)result;
}

