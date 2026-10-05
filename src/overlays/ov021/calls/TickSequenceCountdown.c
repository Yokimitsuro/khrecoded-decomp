#include "nitro/types.h"

typedef struct Sequencer {
    u8 pad00[0x9c];
    u32 flags : 31;
    u32 flagTop : 1;
    u8 pada0[4];
    s32 countdown;
} Sequencer;

extern void RunOverrideTrack(Sequencer *sequencer, u16 overrideId);

void TickSequenceCountdown(Sequencer *sequencer, s32 step)
{
    if (sequencer->countdown != 0) {
        if (sequencer->flags & 0x800000) {
            step = 0x1000;
        }
        sequencer->countdown -= step;
        if (sequencer->countdown <= 0) {
            sequencer->countdown = 0;
            RunOverrideTrack(sequencer, 6);
        }
    }
}
