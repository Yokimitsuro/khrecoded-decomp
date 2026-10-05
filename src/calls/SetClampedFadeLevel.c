#include "nitro/types.h"

void SetClampedFadeLevel(u8 *owner, int level)
{
    if (level > 16) {
        level = 16;
    } else if (level < 0) {
        level = 0;
    }
    *(int *)(owner + 0x6024) = level;
}
