#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x4580];
    u16 visibleCount;
} ItemList;

extern void func_ov075_020cd1d0(ItemList *list, const u32 *categories, u32 categoryCount, BOOL exclude);

u16 BuildCategorySetList(ItemList *list, const u32 *categories, u32 categoryCount, BOOL exclude)
{
    func_ov075_020cd1d0(list, categories, categoryCount, exclude);
    return list->visibleCount;
}
