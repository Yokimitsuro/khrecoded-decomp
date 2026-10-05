#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} SlotPos;

typedef struct {
    int animIndex;
    SlotPos pos;
    u8 pad_0c[0x10];
} SlotEntry;

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
    u8 pad_0000[0xca68];
    SlotEntry slots[26];
    u8 pad_cd40[0xcf54 - 0xcd40];
    ScrollBar bars[2];
} ListWork;

extern u16 data_02060500;
extern void SetSlotPosition(int side, int slotIndex, int x, int y, ListWork *work);
extern void func_ov093_020c0cd0(int index, ListWork *work);

BOOL ScrollBarStepDown(int index, ListWork *work)
{
    ScrollBar *bar = &work->bars[index];
    SlotPos *pos;
    int step;
    int cursor;

    step = 0x10;
    if (index == 0) {
        step = 0x30;
    }
    if (bar->headSlot < 0) {
        bar->cursor = bar->rangeStart - 1;
    }
    cursor = bar->cursor;
    if (bar->visibleCount + cursor < bar->rangeEnd - 1) {
        if (cursor >= bar->rangeStart - 1) {
            bar->visibleCount++;
        } else {
            bar->cursor = cursor + 1;
            if (bar->headSlot > 0) {
                pos = &work->slots[bar->headSlot].pos;
                pos->y += step;
                SetSlotPosition(bar->id, bar->headSlot, pos->x, pos->y, work);
            }
        }
        func_ov093_020c0cd0(bar->id, work);
        return TRUE;
    }
    if (data_02060500 & 0x80) {
        bar->cursor = 0;
        bar->visibleCount = 0;
        if (bar->headSlot >= 0) {
            pos = &work->slots[bar->headSlot].pos;
            pos->y -= step * (bar->rangeStart - 1);
            SetSlotPosition(bar->id, bar->headSlot, pos->x, pos->y, work);
        }
        func_ov093_020c0cd0(bar->id, work);
        return TRUE;
    }
    return FALSE;
}
