#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
} CommState;

extern CommState *gContinueSceneState;
extern s32 IsScreenModeIdle(void);
extern s32 UpdateMenuSelection(void);

s32 MarkCommBusyWhenReady(void)
{
    s32 ready;

    ready = IsScreenModeIdle();
    if (ready != 0) {
        gContinueSceneState->flags = gContinueSceneState->flags | 0x8000;
        return 9;
    }
    UpdateMenuSelection();
    return -1;
}
