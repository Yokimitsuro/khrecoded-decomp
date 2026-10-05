#include "nitro/types.h"

extern u8 *gSoundWork;

BOOL IsSceneState1(void)
{
    return gSoundWork[0xb472e] == 1;
}
