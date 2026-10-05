#include "nitro/types.h"

typedef union CellOffset {
    struct {
        s16 x;
        s16 y;
    } pos;
    u32 raw;
} CellOffset;

CellOffset GetSlotCellOffset(int code)
{
    CellOffset offset;
    u16 slot = code & 7;
    u16 row = (code >> 3) & 3;

    if (code >> 7) {
        offset.pos.y = 0;
        offset.pos.x = row << 4;
    } else {
        int column = slot;

        if (slot >= 3) {
            column = slot - 2;
        }
        offset.pos.x = column << 4;
        offset.pos.y = slot < 3 ? -18 : 18;
    }
    return offset;
}