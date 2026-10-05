#include "nitro/types.h"

typedef struct CursorRange {
    u16 pad_00;
    u16 cursor;
    u16 max;
} CursorRange;

typedef struct CursorOwner {
    u8 pad_00[0x1d4];
    CursorRange *range;
} CursorOwner;

void SetClampedCursor(CursorOwner *owner, u16 value)
{
    CursorRange *range = owner->range;
    u16 result = range->max;
    if (value <= result) {
        result = value;
    }
    range->cursor = result;
}
