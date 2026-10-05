#include "nitro/types.h"

extern void StartSubtitlePlayback(void);

u32 StartSubtitlePlaybackAndReturnState6(void)
{
    StartSubtitlePlayback();
    return 6;
}
