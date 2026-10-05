#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_09[7];
    s32 suppressRefresh;
    u8 pad_14[8];
    u8 dragState;
    u8 pad_1d;
    s16 baseY;
    s16 touchIndex;
    u8 pad_22[6];
    s16 trackTop;
    s16 trackBottom;
    u8 pad_2c[8];
    s32 scrollPixels;
    s32 dragOffset;
    u8 trackRows;
    u8 entryCount;
    u8 pad_3e[2];
    void *upArrow;
    void *downArrow;
    void *thumb;
    void *slots[16];
    void *entries[16];
} ScrollList;

typedef struct ListPosition {
    fx32 x;
    fx32 y;
} ListPosition;

extern void func_ov027_020b9380(void *panel, void *element, ListPosition *position, int mode);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);
extern void RefreshScrollListLayout(ScrollList *list, void *panel);

void SetupScrollList(ScrollList *list, void *panel, BOOL enabled)
{
    u16 i;
    u16 visible;
    ListPosition pos;

    list->touchIndex = -1;
    i = 0;
    list->dragOffset = 0;
    list->dragState = 0;
    list->scrollOffset = 0;
    if (enabled) {
        int track = list->trackRows;
        int rows = list->visibleRows;
        int count = list->itemCount;
        u16 thumb = track * rows / count;
        u16 last;

        if (count >= rows) {
            count = rows;
        }
        visible = count;
        if (thumb <= track) {
            if (thumb < 2) {
                thumb = 2;
            }
            track = thumb;
        }
        list->entryCount = track;
        func_ov027_020b9380(panel, list->thumb, &pos, 0);
        i = 1;
        SetEntrySlotsVisible(panel, list->thumb, TRUE);
        SetEntrySlotsVisible(panel, list->slots[0], TRUE);
        SetEntrySlotsVisible(panel, list->slots[1], TRUE);
        list->entries[0] = list->slots[0];
        list->entries[list->entryCount - 1] = list->slots[1];
        last = list->entryCount - 1;
        for (; i < last; i++) {
            list->entries[i] = list->slots[i + 1];
            SetEntrySlotsVisible(panel, list->entries[i], TRUE);
        }
        for (i = list->entryCount; i < list->trackRows; i++) {
            SetEntrySlotsVisible(panel, list->slots[i], FALSE);
        }
        list->trackTop = (pos.y >> 12) + list->baseY;
        list->trackBottom = list->trackTop + (list->trackRows + 2) * 8;
        if (list->suppressRefresh == 0) {
            RefreshScrollListLayout(list, panel);
        }
        if (list->topIndex > list->itemCount - visible) {
            list->topIndex = list->itemCount - visible;
        }
        if (list->topIndex + visible <= list->cursor) {
            list->cursor = list->topIndex + visible - 1;
        }
        if (list->cursor < 0) {
            list->cursor = 0;
        }
        list->scrollPixels = list->topIndex * list->rowHeight;
        return;
    }
    SetEntrySlotsVisible(panel, list->upArrow, i);
    SetEntrySlotsVisible(panel, list->downArrow, i);
    SetEntrySlotsVisible(panel, list->thumb, i);
    for (; i < list->trackRows; i++) {
        SetEntrySlotsVisible(panel, list->slots[i], FALSE);
    }
}


