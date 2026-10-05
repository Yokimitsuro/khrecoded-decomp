#include "nitro/types.h"

typedef struct ScrollList {
    s8 itemCount;
    s8 visibleCount;
    s8 rowInView;
    s8 scrollOffset;
    s8 cursor;
    u8 flags;
    u8 pad_06[2];
    int scrollPixels;
    int unk_0C;
    int rowPixels;
    int rowHeight;
} ScrollList;

void SetScrollListPosition(ScrollList *list, int scrollOffset, int rowInView)
{
    list->scrollOffset = scrollOffset;
    list->rowInView = rowInView;
    list->cursor = scrollOffset + rowInView;
    list->scrollPixels = scrollOffset * list->rowHeight;
    list->rowPixels = rowInView * list->rowHeight;
}
