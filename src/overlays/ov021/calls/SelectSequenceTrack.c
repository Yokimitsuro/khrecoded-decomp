#include "nitro/types.h"

typedef struct Sequencer {
    u8 pad00[0x14];
    s32 track;
    u8 pad18[4];
    s32 cursor;
    s32 timer;
    u8 pad24[4];
    s32 frame;
    u8 pad2c[0x70 - 0x2c];
    s32 trackStarts[1];
} Sequencer;

extern int func_ov021_020b4c2c(Sequencer *sequencer);

int SelectSequenceTrack(Sequencer *sequencer, int track)
{
    if (sequencer->trackStarts[track] == -1) {
        return 4;
    }
    if (sequencer->track != track) {
        sequencer->track = track;
        sequencer->timer = 0;
        sequencer->frame = 0;
        sequencer->cursor = sequencer->trackStarts[track];
    }
    return func_ov021_020b4c2c(sequencer);
}
