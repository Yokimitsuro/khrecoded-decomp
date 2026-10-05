#include "nitro/types.h"

typedef struct ActiveFlags {
    u32 low : 3;
    u32 paused : 1;
    u32 active : 1;
    u32 extra : 1;
    u32 rest : 26;
} ActiveFlags;

void SetActiveFlags(ActiveFlags *flags, BOOL extra)
{
    flags->paused = 0;
    flags->extra = 0;
    flags->active = 1;
    if (extra) {
        flags->extra = 1;
    }
}
