#include "nitro/types.h"

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    int headSlot;
    u8 pad_10[0x1c];
    int visibleCount;
    int cursor;
    u8 pad_34[0x18];
} ScrollBar;

typedef struct {
    u8 pad_0000[0xcf54];
    ScrollBar bars[2];
} ListWork;

extern void func_ov093_020c0cd0(int index, ListWork *work);

BOOL AdvanceScrollBarStep(int index, ListWork *work)
{
    ScrollBar *bar = &work->bars[index];
    int count = bar->visibleCount;

    if (count == bar->rangeEnd - bar->rangeStart) {
        return FALSE;
    }
    count += bar->rangeStart;
    if (bar->headSlot < 0) {
        bar->cursor = bar->rangeStart - 1;
    }
    if (count > bar->rangeEnd - bar->rangeStart) {
        bar->visibleCount = bar->rangeEnd - bar->rangeStart;
    } else {
        bar->visibleCount = count;
    }
    func_ov093_020c0cd0(bar->id, work);
    return TRUE;
}
