#include "nitro/types.h"

extern u8 *gSoundWork;

BOOL IsSceneState4(void)
{
    return gSoundWork[0xb472e] == 4;
}
