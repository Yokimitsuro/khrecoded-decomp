#include "nitro/types.h"

typedef struct ItemList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} ItemList;

extern void func_ov076_020c9308(ItemList *list, u32 category);

u16 ItemList_FilterByCategory(ItemList *list, u32 category)
{
    func_ov076_020c9308(list, category);
    return list->filteredCount;
}
