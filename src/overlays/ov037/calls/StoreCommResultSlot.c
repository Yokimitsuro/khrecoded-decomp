#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x1c];
    s32 result;
} CommState;

extern CommState *gContinueSceneState;
extern s32 func_ov037_020bb4dc(void);

s32 StoreCommResultSlot(void)
{
    CommState *state = gContinueSceneState;
    s32 result = func_ov037_020bb4dc();

    if (result >= 0) {
        state->result = result;
        return 6;
    }
    return -1;
}
