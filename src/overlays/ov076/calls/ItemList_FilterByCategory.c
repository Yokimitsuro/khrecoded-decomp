#include "nitro/types.h"

typedef struct ItemList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} ItemList;

extern void ItemList_BuildForType(ItemList *list, u32 category);

u16 ItemList_FilterByCategory(ItemList *list, u32 category)
{
    ItemList_BuildForType(list, category);
    return list->filteredCount;
}
