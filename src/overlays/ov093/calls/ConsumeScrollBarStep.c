#include "nitro/types.h"

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    int headSlot;
    u8 pad_10[0x1c];
    int visibleCount;
    int cursorActive;
    u8 pad_34[0x18];
} ScrollBar;

typedef struct {
    u8 pad_0000[0xcf54];
    ScrollBar bars[2];
} ListWork;

extern void func_ov093_020c0cd0(int index, ListWork *work);

BOOL ConsumeScrollBarStep(int index, ListWork *work)
{
    ScrollBar *bar = &work->bars[index];
    int remaining;

    if (bar->visibleCount == 0) {
        return FALSE;
    }
    remaining = bar->visibleCount - bar->rangeStart;
    if (bar->headSlot < 0) {
        bar->cursorActive = 0;
    }
    if (remaining < 0) {
        bar->visibleCount = 0;
    } else {
        bar->visibleCount = remaining;
    }
    func_ov093_020c0cd0(bar->id, work);
    return TRUE;
}
