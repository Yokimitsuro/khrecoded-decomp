#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
} CommState;

extern CommState *gContinueSceneState;
extern void func_ov001_0206a8d4(u16 flags);
extern void func_ov001_0206a72c(int slotIndex);

s32 NotifyCommSlotIfReady(void)
{
    CommState *state = gContinueSceneState;

    if ((state->flags & 2) == 0) {
        func_ov001_0206a8d4(state->flags);
        func_ov001_0206a72c(state->slotIndex);
        return 4;
    }
    return -1;
}
