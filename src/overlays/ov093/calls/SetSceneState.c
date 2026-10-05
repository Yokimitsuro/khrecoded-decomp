#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1cc];
    int state;
    int stateTimer;
    int stateFrames;
} SceneWork;

extern void RuntimeState_SetCondition(int value);

void SetSceneState(int state, SceneWork *work)
{
    work->state = state;
    work->stateTimer = 0;
    work->stateFrames = 0;
    if (state == 6) {
        RuntimeState_SetCondition(1);
    }
}
