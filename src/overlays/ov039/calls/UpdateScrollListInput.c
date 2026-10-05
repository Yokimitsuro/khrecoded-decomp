#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 touchFlags;
    u16 keys;
} ListInput;

typedef struct {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_09[3];
    s32 smoothScroll;
    u8 pad_10[0x0c];
    u8 dragState;
    u8 pad_1d[3];
    s16 touchedRow;
    u8 pad_22[2];
    s32 touchEnabled;
    u8 pad_28[0x0c];
    s32 scrollPixels;
} ScrollList;

extern ListInput *func_ov039_020bca20(void);
extern BOOL func_ov039_020bd888(ScrollList *list, void *owner, ListInput *touch, BOOL changed);
extern BOOL HandleListKeyInput(ScrollList *list, void *owner, int keys, BOOL forceRefresh);

BOOL UpdateScrollListInput(ScrollList *list, void *owner)
{
    ListInput *input = func_ov039_020bca20();
    BOOL changed = FALSE;
    s16 pixels;

    list->touchedRow = -1;
    if (list->smoothScroll != 0 && list->dragState == 0) {
        pixels = list->topIndex * list->rowHeight;
        if (list->scrollPixels != pixels) {
            list->scrollOffset = 0;
            list->scrollPixels = pixels;
            changed = TRUE;
        }
    }
    if (!(input->touchFlags & 3) && !(list->dragState & 2)) {
        list->dragState = 0;
    }
    if (list->touchEnabled != 0 && ((input->touchFlags & 3) || list->dragState != 0)) {
        return func_ov039_020bd888(list, owner, input, changed);
    }
    return HandleListKeyInput(list, owner, input->keys, changed);
}
