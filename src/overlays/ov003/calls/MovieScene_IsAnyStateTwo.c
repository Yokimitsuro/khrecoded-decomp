#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x8b0];
    s32 streamState;
    s32 state;
} MovieScene;

extern MovieScene *NNSi_FndGetCurrentRootHeap(void);

BOOL MovieScene_IsAnyStateTwo(void)
{
    MovieScene *scene = NNSi_FndGetCurrentRootHeap();

    return scene->streamState == 2 || scene->state == 2;
}
