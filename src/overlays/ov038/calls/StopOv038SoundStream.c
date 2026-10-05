#include "nitro/types.h"

extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);

BOOL StopOv038SoundStream(void)
{
    StopSoundStreamAtIndex(0, 0);
    return TRUE;
}
