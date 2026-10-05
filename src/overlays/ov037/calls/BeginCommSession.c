#include "nitro/types.h"

typedef struct CommRequest {
    s8 slotIndex;
    s8 mode;
    s16 paramA;
    s16 paramB;
} CommRequest;

typedef struct CommState {
    s16 mode;
    s16 paramA;
    s16 paramB;
    u16 flags;
    s8 slotIndex;
    u8 pad_09[0x0b];
    s32 task;
    u8 pad_18[0x08];
    s32 counter;
} CommState;

extern CommState *gContinueSceneState;
extern CommState *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov037_020baaa0(void);
extern s32 CreateOverlayTask(int mode);
extern s32 RunCommStepMachine(void);

void *BeginCommSession(CommRequest *request)
{
    gContinueSceneState = NNSi_FndGetCurrentRootHeap();
    gContinueSceneState->mode = request->mode;
    gContinueSceneState->paramA = request->paramA;
    gContinueSceneState->paramB = request->paramB;
    gContinueSceneState->flags = 3;
    func_ov037_020baaa0();
    gContinueSceneState->task = CreateOverlayTask(request->mode);
    gContinueSceneState->slotIndex = request->slotIndex;
    gContinueSceneState->counter = 0;
    return RunCommStepMachine;
}
