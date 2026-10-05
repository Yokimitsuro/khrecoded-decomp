#include "nitro/types.h"

typedef struct {
    int listId;
    int visibleCount;
    int totalCount;
    int slotIndex;
    u8 pad_10[0x1c];
    int scrollTop;
    int selected;
    u8 pad_34[0x18];
} ListCursor;

typedef struct {
    int panelIndex;
    int x;
    int y;
    u8 pad_0c[0x10];
} PanelSlot;

typedef struct {
    u8 pad_0000[0x180];
    ListCursor cursors[2];
    u8 pad_0218[0xca80 - 0x218];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

extern u16 data_02060500;
extern void SetPanelSlotPosition(int listIndex, int slotIndex, int x, int y, MenuScene *scene);
extern void func_ov097_020c08d4(int listId, MenuScene *scene);

BOOL MoveListCursorUp(int listIndex, MenuScene *scene)
{
    ListCursor *cursor = &scene->cursors[listIndex];
    PanelSlot *slot;
    int selected;
    int slotIndex;

    if (cursor->visibleCount <= 1) {
        return FALSE;
    }
    if (cursor->slotIndex < 0) {
        cursor->selected = 0;
    }
    selected = cursor->selected;
    if (cursor->scrollTop + selected > 0) {
        if (selected == 0) {
            cursor->scrollTop--;
        } else {
            cursor->selected = selected - 1;
            slotIndex = cursor->slotIndex;
            if (slotIndex >= 0) {
                if (listIndex == 1) {
                    slot = &scene->subSlots[slotIndex];
                } else {
                    slot = &scene->mainSlots[slotIndex];
                }
                slot->y -= 16;
                SetPanelSlotPosition(cursor->listId, slotIndex, slot->x, slot->y, scene);
            }
        }
        func_ov097_020c08d4(cursor->listId, scene);
        return TRUE;
    }
    if (data_02060500 & 0x40) {
        cursor->selected = cursor->visibleCount - 1;
        cursor->scrollTop = cursor->totalCount - cursor->visibleCount;
        slotIndex = cursor->slotIndex;
        if (slotIndex >= 0) {
            if (listIndex == 1) {
                slot = &scene->subSlots[slotIndex];
            } else {
                slot = &scene->mainSlots[slotIndex];
            }
            slot->y += (cursor->visibleCount - 1) * 16;
            SetPanelSlotPosition(cursor->listId, slotIndex, slot->x, slot->y, scene);
        }
        func_ov097_020c08d4(cursor->listId, scene);
        return TRUE;
    }
    return FALSE;
}
