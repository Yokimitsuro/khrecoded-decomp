#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} PanelPos;

typedef struct {
    int slotIndex;
    PanelPos pos;
    u8 pad_0C[0x8];
} ListPanel;

typedef struct {
    int id;
    int visibleRows;
    int totalRows;
    int panelIndex;
    u8 pad_10[0x1c];
    int topRow;
    int cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
    ListPanel topPanels[6];
    ListPanel bottomPanels[6];
    u8 pad_ca4c[0xcbd0 - 0xca4c];
    ScrollList lists[1];
} MenuScene;

extern u16 data_02060500;
extern void SetListPanelSlotPos(int screen, int panelIndex, int x, int y, MenuScene *scene);
extern void func_ov091_020c0164(int id, MenuScene *scene);

BOOL ScrollListUp(int listIndex, MenuScene *scene)
{
    ScrollList *list = &scene->lists[listIndex];
    PanelPos *pos;

    if (list->panelIndex < 0) {
        list->cursorRow = 0;
    }
    if (list->topRow + list->cursorRow > 0) {
        if (list->cursorRow == 0) {
            list->topRow--;
        } else {
            list->cursorRow--;
            if (list->panelIndex >= 0) {
                pos = &scene->topPanels[list->panelIndex].pos;
                pos->y -= 16;
                SetListPanelSlotPos(0, list->panelIndex, pos->x, pos->y, scene);
            }
        }
        func_ov091_020c0164(list->id, scene);
        return TRUE;
    }
    if (data_02060500 & 0x40) {
        list->cursorRow = list->visibleRows - 1;
        list->topRow = list->totalRows - list->visibleRows;
        if (list->panelIndex >= 0) {
            pos = &scene->topPanels[list->panelIndex].pos;
            pos->y += (list->visibleRows - 1) * 16;
            SetListPanelSlotPos(0, list->panelIndex, pos->x, pos->y, scene);
        }
        func_ov091_020c0164(list->id, scene);
        return TRUE;
    }
    return FALSE;
}
