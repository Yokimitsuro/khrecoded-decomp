#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 touchFlags;
} ListInput;

typedef struct {
    s16 count;
    s16 cursor;
    s16 top;
    u8 thumbOffset;
    u8 pageSize;
    u8 step;
    u8 pad_09[0x13];
    u8 flags;
    u8 pad_1d[0x17];
    int total;
    int velocity;
} ScrollBar;


extern void ClampScrollCursor(ScrollBar *bar);
extern void func_ov039_020bd720(ScrollBar *bar);
extern void SnapScrollToStep(ScrollBar *bar, BOOL updateThumb);

BOOL UpdateScrollInertia(ScrollBar *bar, void *owner, ListInput *input)
{
    BOOL active;
    int limit;
    int damping;

    if ((bar->flags & 2) && bar->pageSize < bar->count) {
        active = TRUE;
    } else {
        active = FALSE;
    }
    if (active) {
        limit = (bar->count - bar->pageSize) * bar->step;
        bar->total -= bar->velocity / 4096;
        if ((input->touchFlags & 3) == 3) {
            bar->velocity = 0;
        }
        if (bar->total > limit) {
            bar->total = limit;
            bar->velocity = 0;
        } else if (bar->total < 0) {
            bar->total = 0;
            bar->velocity = 0;
        } else {
            if (bar->flags & 0x10) {
                damping = bar->velocity / 2;
            } else {
                damping = bar->velocity / 8;
            }
            bar->velocity -= damping;
        }
        ClampScrollCursor(bar);
        if ((u32)((bar->velocity ^ (bar->velocity >> 31)) - (bar->velocity >> 31)) < 0x1000 && bar->flags == 2) {
            bar->flags = 0;
            SnapScrollToStep(bar, TRUE);
        } else {
            func_ov039_020bd720(bar);
        }
    }
    return active;
}
