#include "nitro/types.h"

typedef struct SessionState {
    u8 pad_00[0x20];
    u16 flags;
} SessionState;

extern SessionState *data_ov001_020a0494;

void SetSessionStateBit(BOOL enable, u32 bit)
{
    SessionState *state = data_ov001_020a0494;

    if (enable) {
        state->flags |= (u16)(1 << bit);
        return;
    }
    state->flags &= (u16)~(1 << bit);
}
