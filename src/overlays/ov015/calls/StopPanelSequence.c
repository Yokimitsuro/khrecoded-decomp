#include "nitro/types.h"

typedef struct CursorState {
    u8 pad_00[0x5f];
    s8 sequencePlaying;
} CursorState;

extern CursorState *data_ov015_020812e0;
extern void StopSeqArcOrDefault(int player, int seqArcNo, int fadeFrames);

void StopPanelSequence(void)
{
    if (data_ov015_020812e0->sequencePlaying != 0) {
        StopSeqArcOrDefault(2, 0xc, 0);
        data_ov015_020812e0->sequencePlaying = 0;
    }
}
