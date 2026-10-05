#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
} CommState;

extern CommState *gContinueSceneState;
extern void PushVramState(void);

s32 MarkCommChannelBusy(void)
{
    PushVramState();
    gContinueSceneState->flags = gContinueSceneState->flags | 0x8000;
    return 1;
}
