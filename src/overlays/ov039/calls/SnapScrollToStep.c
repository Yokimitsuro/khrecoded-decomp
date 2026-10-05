#include "nitro/types.h"

typedef struct {
    s16 count;
    s16 cursor;
    s16 top;
    u8 thumbOffset;
    u8 pageSize;
    u8 step;
    u8 pad_09[3];
    int dragging;
    u8 pad_10[0x0c];
    u8 flags;
    u8 pad_1d[0x17];
    int total;
} ScrollBar;

extern void ClampScrollCursor(ScrollBar *bar);
extern void func_ov039_020bd720(ScrollBar *bar);

void SnapScrollToStep(ScrollBar *bar, BOOL updateThumb)
{
    u8 step = bar->step;
    u16 remainder = bar->total % step;
    u16 half = step >> 1;

    if (remainder < half) {
        bar->total -= remainder;
    } else {
        bar->total -= remainder;
        bar->total += bar->step;
    }
    ClampScrollCursor(bar);
    if (updateThumb) {
        func_ov039_020bd720(bar);
    }
    if (!(bar->flags & 2) && bar->dragging != 0) {
        if (remainder < half) {
            bar->total += remainder >> 1;
        } else {
            bar->total -= remainder >> 1;
        }
    }
}
