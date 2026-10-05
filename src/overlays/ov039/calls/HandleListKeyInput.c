#include "nitro/types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_09[3];
    s32 smoothScroll;
    s32 suppressRefresh;
    s32 inputLocked;
    u8 pad_18[0x1c];
    s32 scrollPixels;
    u8 pad_38[0x94];
    s32 seqArcNo;
    s32 cursorSoundIndex;
} ScrollList;

extern u16 data_020604fc;
extern u16 data_02060500;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void RefreshScrollListLayout(ScrollList *list, void *owner);

BOOL HandleListKeyInput(ScrollList *list, void *owner, int keys, BOOL forceRefresh)
{
    u16 itemCount = list->itemCount;
    u16 visibleRows = list->visibleRows;
    u8 changed = forceRefresh ? 2 : 0;
    s16 oldTop;
    BOOL wrapped = FALSE;

    if (list->inputLocked != 0 || !(keys & 0xf0) || (keys & 0xc0) == 0xc0 || (keys & 0x30) == 0x30) {
        if (changed == 0) {
            return FALSE;
        }
        keys = 0;
    }
    if (data_020604fc & 0xc0) {
        keys &= 0xffcf;
    }
    oldTop = list->topIndex;

    if (keys & 0x40) {
        if (list->cursor == 0) {
            if (data_02060500 & 0x40) {
                list->cursor = itemCount - 1;
                PlaySoundEffect(list->seqArcNo, list->cursorSoundIndex);
                wrapped = TRUE;
            }
        } else {
            list->cursor--;
            PlaySoundEffect(list->seqArcNo, list->cursorSoundIndex);
        }
        changed++;
    }
    if (keys & 0x80) {
        if (list->cursor + 1 >= itemCount) {
            if (data_02060500 & 0x80) {
                list->cursor = 0;
                PlaySoundEffect(list->seqArcNo, list->cursorSoundIndex);
                wrapped = TRUE;
            }
        } else {
            list->cursor++;
            PlaySoundEffect(list->seqArcNo, list->cursorSoundIndex);
        }
        changed++;
    }
    if ((keys & 0x20) && list->cursor != 0) {
        if (list->cursor >= visibleRows && list->topIndex != 0) {
            list->cursor -= (s16)visibleRows;
            list->topIndex -= (s16)visibleRows;
            if (list->topIndex < 0) {
                list->cursor -= list->topIndex;
                list->topIndex = 0;
            }
        } else {
            list->cursor = 0;
        }
        changed += 2;
        list->scrollOffset = 0;
        PlaySoundEffect(list->seqArcNo, list->cursorSoundIndex);
    }
    if ((keys & 0x10) && list->cursor < itemCount - 1) {
        s16 maxTop = itemCount - visibleRows;
        if (list->cursor + visibleRows < itemCount && list->topIndex < maxTop) {
            list->cursor += (s16)visibleRows;
            list->topIndex += (s16)visibleRows;
            if (list->topIndex > maxTop) {
                list->cursor -= (s16)(list->topIndex - maxTop);
                list->topIndex = maxTop;
            }
        } else {
            list->cursor = itemCount - 1;
        }
        changed += 2;
        list->scrollOffset = 0;
        PlaySoundEffect(list->seqArcNo, list->cursorSoundIndex);
    }
    if (changed != 0) {
        if (list->cursor < 0) {
            list->topIndex = 0;
            list->cursor = list->topIndex;
            changed--;
        } else if (list->cursor < list->topIndex) {
            list->topIndex = list->cursor;
            list->scrollOffset = 0;
        } else if (list->cursor - visibleRows >= list->topIndex) {
            list->topIndex = list->cursor - visibleRows + 1;
            list->scrollOffset = 0;
        } else {
            changed--;
        }
    }
    list->scrollPixels = list->topIndex * list->rowHeight;
    if (changed != 0 && !wrapped && oldTop != list->topIndex && list->smoothScroll != 0) {
        list->scrollPixels -= (list->topIndex - oldTop) * list->rowHeight / 2;
    }
    if (changed != 0 && list->suppressRefresh == 0) {
        RefreshScrollListLayout(list, owner);
    }
    return changed != 0;
}
