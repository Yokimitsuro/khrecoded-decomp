#include "nitro/types.h"

typedef struct {
    int x;
    int y;
    int pad[3];
} SlotPos;

typedef struct {
    int id;
    int visibleCount;
    int totalCount;
    int slotIndex;
    int pad10[7];
    int scroll;
    int cursor;
    int pad34[6];
} ListPanel;

typedef struct {
    char pad0[0xc9e0];
    SlotPos slots[11];
    char padSlots[0xcacc - 0xc9e0 - 11 * 0x14];
    ListPanel lists[1];
} MenuWork;

extern u16 data_02060500;
extern void SetSlotPosition_020bf7d4(int bank, int slotIndex, int x, int y, MenuWork *work);
extern void func_ov103_020bfe9c(int id, MenuWork *work);

BOOL ScrollListDown_020bfd60(int listIndex, MenuWork *work)
{
    ListPanel *list = &work->lists[listIndex];
    SlotPos *slot;
    if (list->scroll + list->cursor < list->totalCount - 1) {
        if (list->slotIndex < 0) {
            list->cursor = list->visibleCount - 1;
        }
        if (list->cursor >= list->visibleCount - 1) {
            list->scroll++;
        } else {
            list->cursor++;
            if (list->slotIndex >= 0) {
                slot = &work->slots[list->slotIndex];
                slot->y += 0x10;
                SetSlotPosition_020bf7d4(0, list->slotIndex, slot->x, slot->y, work);
            }
        }
        func_ov103_020bfe9c(list->id, work);
        return TRUE;
    }
    if (data_02060500 & 0x80) {
        list->cursor = 0;
        list->scroll = 0;
        if (list->slotIndex >= 0) {
            slot = &work->slots[list->slotIndex];
            slot->y -= (list->visibleCount - 1) * 0x10;
            SetSlotPosition_020bf7d4(0, list->slotIndex, slot->x, slot->y, work);
        }
        func_ov103_020bfe9c(list->id, work);
        return TRUE;
    }
    return FALSE;
}
