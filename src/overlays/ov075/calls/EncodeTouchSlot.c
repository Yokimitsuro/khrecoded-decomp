#include "nitro/types.h"

typedef struct Point16 {
    s16 x;
    s16 y;
} Point16;

u8 EncodeTouchSlot(Point16 pos, int direction)
{
    u32 column = (u16)((pos.x + 8) / 16);
    s16 sign = pos.y >> 15;
    u16 distance = (pos.y ^ sign) - sign;

    if (distance <= 8) {
        return (column << 3) | 0x80 | (direction & 7);
    }
    if (pos.y >= 0) {
        column += 2;
    }
    return column;
}