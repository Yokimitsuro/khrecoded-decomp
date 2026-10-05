#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 pad_08[0x16];
    s16 baseY;
    u8 pad_20[0x1c];
    u8 trackRows;
    u8 entryCount;
    u8 pad_3e[2];
    void *upArrow;
    void *downArrow;
    int anchorId;
    u8 pad_4c[0x40];
    void *entries[1];
} ScrollList;

typedef struct ListPosition {
    fx32 x;
    fx32 y;
} ListPosition;

extern void func_ov027_020b9380(void *panel, int elementId, ListPosition *position, int mode);
extern void func_ov027_020b91e8(void *panel, void *element, ListPosition *position, int mode);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);

void RefreshScrollListLayout(ScrollList *list, void *panel)
{
    ListPosition pos;
    u16 i = 0;

    func_ov027_020b9380(panel, list->anchorId, &pos, 0);
    pos.y += list->baseY << 12;
    if (list->itemCount <= list->visibleRows) {
        for (; i < list->entryCount; i++) {
            pos.y += 0x8000;
            func_ov027_020b91e8(panel, list->entries[i], &pos, 0);
        }
    } else {
        pos.y += (list->scrollOffset + ((list->topIndex * ((list->trackRows - list->entryCount) * 8)) / (list->itemCount - list->visibleRows) + 8)) << 12;
        for (; i < list->entryCount; i++) {
            func_ov027_020b91e8(panel, list->entries[i], &pos, 0);
            pos.y += 0x8000;
        }
    }
    SetEntrySlotsVisible(panel, list->upArrow, list->topIndex > 0);
    SetEntrySlotsVisible(panel, list->downArrow, list->topIndex + list->visibleRows < list->itemCount);
}


