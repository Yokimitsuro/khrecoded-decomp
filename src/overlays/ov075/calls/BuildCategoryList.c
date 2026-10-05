#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x4580];
    u16 visibleCount;
} ItemList;

extern void func_ov075_020cd0c0(ItemList *list, u32 category);

u16 BuildCategoryList(ItemList *list, u32 category)
{
    func_ov075_020cd0c0(list, category);
    return list->visibleCount;
}
