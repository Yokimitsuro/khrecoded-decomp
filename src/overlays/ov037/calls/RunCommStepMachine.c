#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x18];
    s32 step;
} CommState;

extern CommState *gContinueSceneState;
extern s32 (*gCommunicationStateHandlers[])(void);
extern void func_ov037_020baa90(int flag);
extern void func_ov037_020baa84(void);

s32 RunCommStepMachine(void)
{
    s32 next;

    do {
        gContinueSceneState->flags &= 0x7fff;
        next = gCommunicationStateHandlers[gContinueSceneState->step]();
        if (next >= 0) {
            gContinueSceneState->step = next;
        }
    } while (gContinueSceneState->flags & 0x8000);
    if (gContinueSceneState->flags & 8) {
        func_ov037_020baa90(0);
    }
    if (gContinueSceneState->flags & 4) {
        func_ov037_020baa84();
    }
    return 0;
}
