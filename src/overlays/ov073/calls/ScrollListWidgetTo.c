#include "nitro/types.h"

typedef struct ListPage {
    u16 id;
    u16 height;
    u32 data;
} ListPage;

typedef struct ListLayout {
    u8 pad_00[8];
    ListPage pages[1];
} ListLayout;

typedef struct ListResource {
    u8 pad_00[4];
    ListLayout *layout;
} ListResource;

typedef struct ListWidget {
    void (*onChange)(void);
    ListResource *resource;
    u8 pad_08[0x98];
    int busy;
    int pageIndex;
} ListWidget;

extern void func_ov073_020c3d80(ListWidget *list);
extern void func_ov073_020c3e44(ListWidget *list);

void ScrollListWidgetTo(ListWidget *list, int target)
{
    int current = (list->resource->layout->pages[list->pageIndex].height - 2) / 16;

    if (list->busy == 0) {
        if (target >= current) {
            for (; current < target; current++) {
                func_ov073_020c3d80(list);
            }
        } else {
            for (; target < current; target++) {
                func_ov073_020c3e44(list);
            }
        }
    }
}
