#include "nitro/types.h"

typedef struct ListCursor {
    s8 itemCount;
    s8 visibleCount;
    s8 rowInView;
    s8 scrollOffset;
    s8 cursor;
    u8 clampCursor : 1;
} ListCursor;

extern u32 ReadHalfword(void *input);

u32 UpdateListCursor(void *input, ListCursor *list, u32 keys)
{
    s8 delta = 0;
    s8 oldCursor = list->cursor;
    u32 result = 0;
    s8 zero = 0;
    int position;

    if (input != NULL) {
        if (ReadHalfword(input) & 0x40) {
            delta--;
        }
        if (ReadHalfword(input) & 0x80) {
            delta++;
        }
    } else {
        if (keys & 0x40) {
            delta--;
        }
        if (keys & 0x80) {
            delta++;
        }
    }

    position = list->cursor + delta;
    if (position >= list->itemCount || position < 0) {
        if (keys & 0xc0) {
            list->cursor += delta;
        }
    } else {
        list->cursor = position;
        list->rowInView += delta;
    }

    if (list->clampCursor) {
        if (list->cursor >= list->itemCount) {
            list->cursor = list->itemCount - 1;
        }
        if (list->cursor < 0) {
            list->cursor = zero;
        }
    } else {
        if (list->cursor >= list->itemCount) {
            list->cursor = zero;
            list->rowInView = zero;
            list->scrollOffset = zero;
            result |= 2;
        }
        if (list->cursor < 0) {
            s8 last = list->itemCount - 1;
            result |= 2;
            list->scrollOffset = list->itemCount - list->visibleCount;
            list->rowInView = list->visibleCount - 1;
            list->cursor = last;
            if (list->scrollOffset < 0) {
                list->rowInView = last;
                list->scrollOffset = zero;
            }
        }
    }

    if (list->rowInView >= list->visibleCount) {
        list->rowInView = list->visibleCount - 1;
        list->scrollOffset++;
        result |= 2;
    } else if (list->rowInView < 0) {
        list->rowInView = zero;
        list->scrollOffset--;
        result |= 2;
    }

    if (oldCursor != list->cursor) {
        result |= 1;
    }
    return result;
}
