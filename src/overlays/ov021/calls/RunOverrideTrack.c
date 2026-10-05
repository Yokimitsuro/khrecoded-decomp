#include "nitro/types.h"

typedef struct {
    u8 pad00[0x30];
    s32 value;
} SequenceSource;

typedef struct Sequencer {
    u8 pad00[0x10];
    SequenceSource *source;
    s32 track;
    u8 pad18[4];
    s32 cursor;
    s32 timer;
    u8 pad24[4];
    s32 frame;
    u8 pad2c[0x98 - 0x2c];
    s32 sourceValue;
    u8 pad9c[6];
    u16 overrideId;
} Sequencer;

extern int SelectSequenceTrack(Sequencer *sequencer, int track);

void RunOverrideTrack(Sequencer *sequencer, u16 overrideId)
{
    s32 track;
    s32 timer;
    s32 cursor;
    s32 frame;

    sequencer->overrideId = overrideId;
    sequencer->sourceValue = sequencer->source->value;
    if (sequencer->track == 10) {
        sequencer->track = 0;
    }
    track = sequencer->track;
    timer = sequencer->timer;
    cursor = sequencer->cursor;
    frame = sequencer->frame;
    SelectSequenceTrack(sequencer, 10);
    sequencer->timer = timer;
    sequencer->track = track;
    sequencer->cursor = cursor;
    sequencer->frame = frame;
    sequencer->overrideId = 0;
}
