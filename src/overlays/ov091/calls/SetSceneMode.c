#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xcc68];
    s32 mode;
    s32 modeStep;
    s32 modeTimer;
} MenuScene;

void SetSceneMode(s32 mode, MenuScene *scene)
{
    scene->mode = mode;
    scene->modeStep = 0;
    scene->modeTimer = 0;
}
