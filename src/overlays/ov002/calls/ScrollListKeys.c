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

extern u32 UpdateListCursorKeys(u32 keys, ScrollList *list);

u32 ScrollListKeys(u32 keys, ScrollList *list)
{
    u32 result = UpdateListCursorKeys(keys, list);
    list->scrollPixels = list->scrollOffset * list->rowHeight;
    list->rowPixels = list->rowInView * list->rowHeight;
    return result;
}
