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
    int maxScrollPixels;
    int rowPixels;
    int rowHeight;
} ScrollList;

extern void MI_CpuFill8(void *dst, int value, u32 size);

void InitScrollList(ScrollList *list, int itemCount, int visibleCount, int rowHeight)
{
    MI_CpuFill8(list, 0, sizeof(ScrollList));
    list->itemCount = itemCount;
    list->visibleCount = visibleCount;
    list->rowHeight = rowHeight;
    list->maxScrollPixels = rowHeight * (itemCount - visibleCount);
}
