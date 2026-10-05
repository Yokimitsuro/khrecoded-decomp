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
extern fx32 FX_Div(fx32 numer, fx32 denom);

void EaseScrollTrack(int trackIndex)
{
    ScrollTrack *tracks = data_ov097_020c2540->scrollTracks;
    ScrollTrack *entry = &tracks[trackIndex];

    entry->current += (fx32)(((s64)(tracks[trackIndex].target - entry->current) * FX_Div(0x7b, 0x266) +
                               0x800) >> 12);
}
