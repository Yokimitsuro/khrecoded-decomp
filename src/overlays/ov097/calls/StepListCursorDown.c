#include "nitro/types.h"

typedef struct {
    int panelIndex;
    int x;
    int y;
    u8 pad_0c[0x10];
} PanelSlot;

typedef struct {
    int handle;
    int visibleRows;
    int totalRows;
    int slotIndex;
    u8 pad_10[0x1c];
    int scrollRow;
    int cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    u8 pad_0000[0x180];
    ScrollList lists[2];
    u8 pad_0218[0xca80 - 0x218];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

extern u16 data_02060500;
extern void SetPanelSlotPosition(int listIndex, int slotIndex, int x, int y, MenuScene *scene);
extern void func_ov097_020c08d4(int handle, MenuScene *scene);

BOOL StepListCursorDown(int listIndex, MenuScene *scene)
{
    ScrollList *list = &scene->lists[listIndex];
    PanelSlot *slot;
    int cursor;
    int slotIndex;

    if (list->visibleRows <= 1) {
        return FALSE;
    }
    if (list->slotIndex < 0) {
        list->cursorRow = list->visibleRows - 1;
    }
    cursor = list->cursorRow;
    if (list->scrollRow + cursor < list->totalRows - 1) {
        if (cursor >= list->visibleRows - 1) {
            list->scrollRow++;
        } else {
            list->cursorRow = cursor + 1;
            slotIndex = list->slotIndex;
            if (slotIndex >= 0) {
                if (listIndex == 1) {
                    slot = &scene->subSlots[slotIndex];
                } else {
                    slot = &scene->mainSlots[slotIndex];
                }
                slot->y += 16;
                SetPanelSlotPosition(list->handle, slotIndex, slot->x, slot->y, scene);
            }
        }
        func_ov097_020c08d4(list->handle, scene);
        return TRUE;
    }
    if (data_02060500 & 0x80) {
        list->cursorRow = 0;
        list->scrollRow = 0;
        slotIndex = list->slotIndex;
        if (slotIndex >= 0) {
            if (listIndex == 1) {
                slot = &scene->subSlots[slotIndex];
            } else {
                slot = &scene->mainSlots[slotIndex];
            }
            slot->y -= (list->visibleRows - 1) * 16;
            SetPanelSlotPosition(list->handle, slotIndex, slot->x, slot->y, scene);
        }
        func_ov097_020c08d4(list->handle, scene);
        return TRUE;
    }
    return FALSE;
}
