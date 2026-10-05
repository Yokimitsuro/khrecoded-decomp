#include "nitro/types.h"

typedef struct {
    s16 count;
    s16 cursor;
    s16 top;
    u8 thumbOffset;
    u8 pageSize;
    u8 step;
    u8 pad_09[0x2b];
    int total;
} ScrollBar;

void ClampScrollCursor(ScrollBar *bar)
{
    u16 visible = bar->count < bar->pageSize ? bar->count : bar->pageSize;

    bar->top = bar->total / bar->step;
    if (bar->top + visible >= bar->count) {
        bar->top = bar->count - visible;
    }
    if (bar->cursor < bar->top) {
        bar->cursor = bar->top;
    } else if (bar->cursor - visible >= bar->top) {
        bar->cursor = bar->top + visible - 1;
    }
    if (bar->cursor == bar->top && bar->total % bar->step != 0) {
        bar->cursor++;
    }
}
