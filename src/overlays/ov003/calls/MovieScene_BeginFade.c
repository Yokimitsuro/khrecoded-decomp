#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x8b4];
    s32 state;
    u8 pad_8b8[2];
    u8 fadeMode;
    u8 pad_8bb;
    s32 fadeTarget;
    s32 fadeStep;
} MovieScene;

extern MovieScene *data_ov003_020658c0;
extern void ActivateSubtitleStream(void);

void MovieScene_BeginFade(u8 mode, s32 target)
{
    MovieScene *scene = data_ov003_020658c0;

    scene->fadeTarget = target;
    scene->fadeStep = -1;
    scene->fadeMode = mode;
    if (scene->state == 1) {
        scene->state = 2;
        ActivateSubtitleStream();
    }
}
