#include "nitro/types.h"

typedef struct SharedState {
    u8 unk_00;
    u8 needsUpdate;
    u8 pad_02[0x120 - 0x02];
    u32 unk_120;
} SharedState;

extern SharedState *func_ov039_020bc650(void);

void SetSharedStateValue(u32 value) {
    SharedState *state = func_ov039_020bc650();

    state->unk_120 = value;
    state->needsUpdate = TRUE;
}
