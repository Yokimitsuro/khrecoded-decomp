#include "nitro/types.h"

int FindFirstClearFlag(u8 *owner)
{
    u16 flags = *(u16 *)(owner + 0x4612);
    int bit;

    for (bit = 0; bit < 16; bit++) {
        if (!(flags & (1 << bit))) {
            return bit;
        }
    }
    return bit;
}
