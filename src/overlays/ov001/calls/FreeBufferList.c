#include "nitro/types.h"

typedef struct BufferItem {
    u8 data[0x30];
} BufferItem;

typedef struct BufferList {
    BufferItem *items;
    s8 count;
} BufferList;

extern int func_ov001_0206a918(BufferItem *item);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeBufferList(BufferList *list)
{
    int i;

    for (i = 0; i < list->count; i++) {
        func_ov001_0206a918(&list->items[i]);
    }
    NNSi_FndFreeFromDefaultHeap(list->items);
}
