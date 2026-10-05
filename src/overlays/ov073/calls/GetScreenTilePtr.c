#include "nitro/types.h"

u16 *GetScreenTilePtr(u16 *screen, int x, int y)
{
    u16 offset = (u16)((x / 32) << 10) + (u16)(y << 5);

    offset += (u16)(x % 32);
    return &screen[offset];
}
