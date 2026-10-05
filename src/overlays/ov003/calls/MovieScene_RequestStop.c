#include "nitro/types.h"

typedef struct MovieScene {
    u16 unk_00;
    u16 flags;
} MovieScene;

extern MovieScene *NNSi_FndGetCurrentRootHeap(void);

int MovieScene_RequestStop(void)
{
    MovieScene *scene = NNSi_FndGetCurrentRootHeap();

    scene->flags |= 8;
    if (scene->flags & 0x10) {
        return -2;
    }
    return 0;
}
