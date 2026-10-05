#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 target;
    fx32 current;
} ScrollTrack;

typedef struct {
    u8 pad_0000[0xf084];
    ScrollTrack scrollTracks[2];
} MenuScene;

extern MenuScene *data_ov097_020c2540;

void ResetScrollTrack(int trackIndex)
{
    ScrollTrack *tracks = data_ov097_020c2540->scrollTracks;

    tracks[trackIndex].target = 0;
    tracks[trackIndex].current = 0;
}
